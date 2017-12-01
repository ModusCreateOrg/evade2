
#include <stdbool.h>
#include <stdint.h>

#define OSC_SAMPLERATE (16000)
#define OSC_MOD_MIN (0)
#define OSC_MOD_MAX (255)
#define OSC_ISR_PRESCALER_DIV (8)
#define OSC_TICKRATE_MAX (OSC_SAMPLERATE/ISR_PRESCALER_DIV)
/*
OSC period is 2**16 so Nyquist corresponds to 2**16/2. Note that's way too high
for square waves to sound OK.
*/
#define OSC_PHASE_INC_MAX (0x3FFF)
#define OSC_TICK_CALLBACK_COUNT (2)

enum osc_channels_e {
	OSC_CH_ZERO = 0,
	OSC_CH_ONE,
	OSC_CH_TWO,
	OSC_CH_THREE,
	OSC_CH_COUNT,
};

struct osc_params {
	uint8_t  mod;
	uint8_t  vol;
	uint16_t phase_increment;
};

extern struct osc_params osc_params_array[OSC_CH_COUNT];

typedef void (*osc_tick_callback)(const uint8_t cb_index, void *priv);

void osc_setup(void);

/* tick_hz < 8 are currently not supported */
void osc_set_tick_rate(const uint8_t callback_idx, const uint16_t rate_hz);
void osc_set_tick_callback(const uint8_t callback_idx, const osc_tick_callback cb, const void *priv);
void osc_get_tick_callback(const uint8_t callback_idx, osc_tick_callback *cb, void **priv);
