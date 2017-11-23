
#include <stddef.h>
#include <string.h>
#include <avr/interrupt.h>
#include "osc.h"

static void osc_reset(void);
static void osc_setactive(const uint8_t active_flag);

struct callback_info {
	uint8_t callback_prescaler_counter;
	uint8_t callback_prescaler_preset;
	osc_tick_callback cb;
	void *priv;
};

uint8_t __attribute__((used)) osc_isr_reenter = 0;
uint8_t osc_int_count __attribute__((used));
struct osc_params osc_params_array[OSC_CH_COUNT] __attribute__((used));
uint16_t osc_pha_acc_array[OSC_CH_COUNT] __attribute__((used));
struct callback_info osc_cb[OSC_TICK_CALLBACK_COUNT];

void osc_setup(void)
{
	osc_reset();
	TCCR4A = 0b01000010;    // Fast-PWM 8-bit
	TCCR4B = 0b00000001;    // currently 31250Hz
	OCR4C  = 0xFF;          // Resolution to 8-bit (TOP=0xFF)
}

static void osc_reset(void)
{
	osc_setactive(0);
	memset(osc_params_array, 0, sizeof(osc_params_array));
	memset(osc_cb, 0, sizeof(osc_cb));
	for (uint8_t i=0; i<OSC_CH_COUNT; i++) {
		/* set modulation to 50% duty cycle */
		osc_params_array[i].mod = 0x7F;
	}
	for (uint8_t i=0; i<OSC_TICK_CALLBACK_COUNT; i++) {
		osc_cb[i].callback_prescaler_preset = 255;
		osc_cb[i].callback_prescaler_counter = 255;
	}
	osc_params_array[OSC_CH_THREE].phase_increment = 0x0001; // Seed LFSR
}

static void osc_setactive(const uint8_t active_flag)
{
	TIMSK4 = active_flag ? 0b00000100 : 0b00000000;
	OCR4A  = OSC_DC_OFFSET;
}

#if 0
void osc_toggleactive(void)
{
	TIMSK4 = TIMSK4 ^ 0b00000100; /* toggle disable/enable interrupt */
}
#endif

void osc_set_tick_rate(const uint8_t callback_idx, const uint16_t rate_hz)
{
	const uint8_t div = OSC_SAMPLERATE/OSC_ISR_PRESCALER_DIV/rate_hz-1;
	osc_cb[callback_idx].callback_prescaler_preset = div;
}

void osc_set_tick_callback(const uint8_t callback_idx, const osc_tick_callback cb, const void *priv)
{
	osc_cb[callback_idx].cb = cb;
	osc_cb[callback_idx].priv = (void *)priv;
	if (cb) {
		/* trigger callback ASAP */
		osc_cb[callback_idx].callback_prescaler_counter = 0;
	}
	/* Turn interrupts on/off as needed */
	osc_setactive(osc_cb[0].cb || osc_cb[1].cb);
}

void osc_get_tick_callback(const uint8_t callback_idx, osc_tick_callback *cb, void **priv)
{
	if (cb) {
		*cb = osc_cb[callback_idx].cb;
	}
	if (priv) {
		*priv = osc_cb[callback_idx].priv;
	}
}

static __attribute__((used)) void osc_tick_handler(void)
{
	for (uint8_t n = 0; n < OSC_TICK_CALLBACK_COUNT; n++) {
		struct callback_info *cbi = &osc_cb[n];
		/* channel tick is due when callback_prescaler_counter underflows */
		if (cbi->callback_prescaler_counter != 255) {
			if (!cbi->cb) {
				/*
				Reset the counter to the highest value when the
				callback is disabled, this way when there is only
				one callback registered (99% of the time) the disabled
				callback is never going to trigger a tick handler.
				*/
				cbi->callback_prescaler_counter = 255;
			}
			continue;
		}
		if (cbi->cb) {
			cbi->cb(n, cbi->priv);
		}
		cbi->callback_prescaler_counter = cbi->callback_prescaler_preset;
	}
}

#define ASM_EOL "\n\t"

ISR(TIMER4_OVF_vect, ISR_NAKED)
{
	asm volatile(
"	push r2                                                        " ASM_EOL
"	in   r2,                    __SREG__                           " ASM_EOL
"	push r18                                                       " ASM_EOL
"	lds  r18,                   osc_int_count                      " ASM_EOL
"	dec  r18                                                       " ASM_EOL
"	sts  osc_int_count,         r18                                " ASM_EOL
"	;push a new sample at half the interrupt rate                  " ASM_EOL
"	andi r18,                   1                                  " ASM_EOL
"	breq continue                                                  " ASM_EOL
"	pop  r18                                                       " ASM_EOL
"	out  __SREG__,              r2                                 " ASM_EOL
"	pop  r2                                                        " ASM_EOL
"	reti                                                           " ASM_EOL
"continue:                                                         " ASM_EOL
"	push r27                                                       " ASM_EOL
"	push r26                                                       " ASM_EOL
"	push r0                                                        " ASM_EOL
"	push r1                                                        " ASM_EOL
"; OSC 2 advance phase accumulator                                 " ASM_EOL
"	lds  r18,                   osc_params_array+2*%[osz]+%[phi]   " ASM_EOL
"	lds  r0,                    osc_pha_acc_array+2*%[asz]         " ASM_EOL
"	add  r0,                    r18                                " ASM_EOL
"	sts  osc_pha_acc_array+2*%[asz],          r0                   " ASM_EOL
"	lds  r18,                   osc_params_array+2*%[osz]+%[phi]+1 " ASM_EOL
"	lds  r1,                    osc_pha_acc_array+2*%[asz]+1       " ASM_EOL
"	adc  r1,                    r18                                " ASM_EOL
"	sts  osc_pha_acc_array+2*%[asz]+1,        r1                   " ASM_EOL
"; OSC 2 square waveform                                           " ASM_EOL
"	lds  r27,                   osc_params_array+2*%[osz]+%[mod]   " ASM_EOL
"	cp   r1,                    r27                                " ASM_EOL
"	lds  r26,                   osc_params_array+2*%[osz]+%[vol]   " ASM_EOL
"	brcs 1f                                                        " ASM_EOL
"	neg  r26                                                       " ASM_EOL
"1:                                                                " ASM_EOL
"; OSC 0 advance phase accumulator                                 " ASM_EOL
"	lds  r18,                   osc_params_array+0*%[osz]+%[phi]   " ASM_EOL
"	lds  r0,                    osc_pha_acc_array+0*%[asz]         " ASM_EOL
"	add  r0,                    r18                                " ASM_EOL
"	sts  osc_pha_acc_array+0*%[asz],          r0                   " ASM_EOL
"	lds  r18,                   osc_params_array+0*%[osz]+%[phi]+1 " ASM_EOL
"	lds  r1,                    osc_pha_acc_array+0*%[asz]+1       " ASM_EOL
"	adc  r1,                    r18                                " ASM_EOL
"	sts  osc_pha_acc_array+0*%[asz]+1,        r1                   " ASM_EOL
"; OSC 0 square waveform                                           " ASM_EOL
"	lds  r27,                   osc_params_array+0*%[osz]+%[mod]   " ASM_EOL
"	cp   r1,                    r27                                " ASM_EOL
"	lds  r27,                   osc_params_array+0*%[osz]+%[vol]   " ASM_EOL
"	brcs 1f                                                        " ASM_EOL
"	neg  r27                                                       " ASM_EOL
"1:                                                                " ASM_EOL
"	add  r26,                   r27                                " ASM_EOL
"; OSC 1 advance phase accumulator                                 " ASM_EOL
"	lds  r18,                   osc_params_array+1*%[osz]+%[phi]   " ASM_EOL
"	lds  r0,                    osc_pha_acc_array+1*%[asz]         " ASM_EOL
"	add  r0,                    r18                                " ASM_EOL
"	sts  osc_pha_acc_array+1*%[asz],          r0                   " ASM_EOL
"	lds  r18,                   osc_params_array+1*%[osz]+%[phi]+1 " ASM_EOL
"	lds  r1,                    osc_pha_acc_array+1*%[asz]+1       " ASM_EOL
"	adc  r1,                    r18                                " ASM_EOL
"	sts  osc_pha_acc_array+1*%[asz]+1,        r1                   " ASM_EOL
"; OSC 1 square waveform                                           " ASM_EOL
"	lds  r27,                   osc_params_array+1*%[osz]+%[mod]   " ASM_EOL
"	cp   r1,                    r27                                " ASM_EOL
"	lds  r27,                   osc_params_array+1*%[osz]+%[vol]   " ASM_EOL
"	brcs 1f                                                        " ASM_EOL
"	neg  r27                                                       " ASM_EOL
"1:                                                                " ASM_EOL
"	add  r26,                   r27                                " ASM_EOL
"; OSC 3 noise generator                                           " ASM_EOL
"	ldi  r27,                   1                                  " ASM_EOL
"	lds  r0,                    osc_params_array+3*%[osz]+%[phi]   " ASM_EOL
"	lds  r1,                    osc_params_array+3*%[osz]+%[phi]+1 " ASM_EOL
"	add  r0,                    r0                                 " ASM_EOL
"	adc  r1,                    r1                                 " ASM_EOL
"	sbrc r1,                    7                                  " ASM_EOL
"	eor  r0,                    r27                                " ASM_EOL
"	sbrc r1,                    6                                  " ASM_EOL
"	eor  r0,                    r27                                " ASM_EOL
"	sts  osc_params_array+3*%[osz]+%[phi],   r0                    " ASM_EOL
"	sts  osc_params_array+3*%[osz]+%[phi]+1, r1                    " ASM_EOL
"; OSC 3 continued                                                 " ASM_EOL
"	lds  r27,                   osc_params_array+3*%[osz]+%[vol]   " ASM_EOL
"	sbrc r1,                    7                                  " ASM_EOL
"	neg  r27                                                       " ASM_EOL
"	add  r26,                   r27                                " ASM_EOL
"; add DC offset                                                   " ASM_EOL
"	ldi  r27,                   %[dc]                              " ASM_EOL
"	add  r26,                   r27                                " ASM_EOL
"	sts  %[reg],                r26                                " ASM_EOL
"; tick handler prescaler                                          " ASM_EOL
"	lds  r18,                   osc_int_count                      " ASM_EOL
"	and  r18,                   r18                                " ASM_EOL
"	;check if a channel tick is due only once every                " ASM_EOL
"	;8 interrupts                                                  " ASM_EOL
"	brne isr_done                                                  " ASM_EOL
"	ldi  r18,                   %[div]                             " ASM_EOL
"	sts  osc_int_count,         r18                                " ASM_EOL
"; check if a tick is due for each OSC                             " ASM_EOL
"	clr  r27                                                       " ASM_EOL
"	lds  r26,                   osc_cb+0*%[csz]+%[pre]             " ASM_EOL
"	subi r26,                   1                                  " ASM_EOL
"	;Use the carry from r26-1 to make r27 undeflow                 " ASM_EOL
"	;instead of branching. (saves 9 cycles in total)               " ASM_EOL
"	sbci r27,                   0                                  " ASM_EOL
"	sts  osc_cb+0*%[csz]+%[pre], r26                               " ASM_EOL
"	lds  r26,                   osc_cb+1*%[csz]+%[pre]             " ASM_EOL
"	subi r26,                   1                                  " ASM_EOL
"	sbci r27,                   0                                  " ASM_EOL
"	sts  osc_cb+1*%[csz]+%[pre], r26                               " ASM_EOL
"	;r27 underflow means at least one channel's                    " ASM_EOL
"	;tick is due.                                                  " ASM_EOL
"	brne call_playroutine                                          " ASM_EOL
"isr_done:                                                         " ASM_EOL
"	pop  r1                                                        " ASM_EOL
"	pop  r0                                                        " ASM_EOL
"	pop  r26                                                       " ASM_EOL
"	pop  r27                                                       " ASM_EOL
"	pop  r18                                                       " ASM_EOL
"	out  __SREG__,              r2                                 " ASM_EOL
"	pop  r2                                                        " ASM_EOL
"	reti                                                           " ASM_EOL
"call_playroutine:                                                 " ASM_EOL
"	lds  r26,                   osc_isr_reenter                    " ASM_EOL
"	cpi  r26,                   0                                  " ASM_EOL
"	brne isr_done                                                  " ASM_EOL
"	;r27 is always nonzero when reaching this point                " ASM_EOL
"	sts  osc_isr_reenter,       r27                                " ASM_EOL
"	sei                                                            " ASM_EOL
"	push r19                                                       " ASM_EOL
"	push r20                                                       " ASM_EOL
"	push r21                                                       " ASM_EOL
"	push r22                                                       " ASM_EOL
"	push r23                                                       " ASM_EOL
"	push r24                                                       " ASM_EOL
"	push r25                                                       " ASM_EOL
"	push r30                                                       " ASM_EOL
"	push r31                                                       " ASM_EOL

"	clr  r1                                                        " ASM_EOL
"	call osc_tick_handler                                          " ASM_EOL

"	sts  osc_isr_reenter,       r1                                 " ASM_EOL
"	pop  r31                                                       " ASM_EOL
"	pop  r30                                                       " ASM_EOL
"	pop  r25                                                       " ASM_EOL
"	pop  r24                                                       " ASM_EOL
"	pop  r23                                                       " ASM_EOL
"	pop  r22                                                       " ASM_EOL
"	pop  r21                                                       " ASM_EOL
"	pop  r20                                                       " ASM_EOL
"	pop  r19                                                       " ASM_EOL

"	pop  r1                                                        " ASM_EOL
"	pop  r0                                                        " ASM_EOL
"	pop  r26                                                       " ASM_EOL
"	pop  r27                                                       " ASM_EOL
"	pop  r18                                                       " ASM_EOL
"	out  __SREG__,              r2                                 " ASM_EOL
"	pop  r2                                                        " ASM_EOL
"	reti                                                           " ASM_EOL
	::
	[reg] "M" _SFR_MEM_ADDR(OCR4A),
	[div] "M" (OSC_ISR_PRESCALER_DIV*2),
	[dc]  "M" OSC_DC_OFFSET,
	[osz] "M" (sizeof(struct osc_params)),
	[asz] "M" (sizeof(uint16_t)),
	[csz] "M" (sizeof(struct callback_info)),
	[pre] "M" (offsetof(struct callback_info, callback_prescaler_counter)),
	[phi] "M" (offsetof(struct osc_params, phase_increment)),
	[mod] "M" (offsetof(struct osc_params, mod)),
	[vol] "M" (offsetof(struct osc_params, vol))
	);
}
