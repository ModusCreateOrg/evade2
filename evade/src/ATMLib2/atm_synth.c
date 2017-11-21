
#include <string.h>
#include <avr/pgmspace.h>

#include "atm_synth.h"

/* #define log_cmd() to oblivion */
#define log_cmd(a,b,c,d)

#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))

struct atm_synth_state atmlib_state;

#define ATMLIB_TICKRATE_MAX (255)
#define MAX_VOLUME (63)
#define LAST_NOTE (63)
const uint16_t noteTable[64] PROGMEM = {
	0,
	274,  291,  308,  326,  346,  366,  388,  411,  435,  461,  489,  518,
	549,  581,  616,  652,  691,  732,  776,  822,  871,  923,  978,  1036,
	1097, 1163, 1232, 1305, 1383, 1465, 1552, 1644, 1742, 1845, 1955, 2071,
	2195, 2325, 2463, 2610, 2765, 2930, 3104, 3288, 3484, 3691, 3910, 4143,
	4389, 4650, 4927, 5220, 5530, 5859, 6207, 6577, 6968, 7382, 7821, 8286,
	8779, 9301, 9854,
};

static uint16_t note_index_2_phase_inc(const uint8_t note_idx)
{
	return pgm_read_word(&noteTable[(note_idx) & 0x3F]);
}

struct atm_channel_state channels[OSC_CH_COUNT];

static void atm_synth_score_tick_handler(uint8_t cb_index, void *priv);
static void atm_synth_sfx_tick_handler(uint8_t cb_index, void *priv);
static void atm_synth_ext_tick_handler(uint8_t cb_index, void *priv);

#define pattern_index(ch_ptr) ((ch_ptr)->pstack[(ch_ptr)->pstack_index].pattern_index)
#define pattern_cmd_ptr(ch_ptr) ((ch_ptr)->pstack[(ch_ptr)->pstack_index].next_cmd_ptr)
#define pattern_repetition_counter(ch_ptr) ((ch_ptr)->pstack[(ch_ptr)->pstack_index].repetitions_counter)

/* ---- */

static void fetch_cmd(const uint8_t ch_index, struct atm_channel_state *ch, struct atm_cmd_data *cmd)
{
	(void)(ch_index);
	/*
	Reading the command first and then its parameters
	takes up more progmem so we read a fixed amount.
	maximum command size is 4 right now
	*/
	memcpy_P(cmd, pattern_cmd_ptr(ch), sizeof(struct atm_cmd_data));
	/* Increment score pointer with the real command size */
	const uint8_t csz = cmd->id & 0x80 ? ((cmd->id >> 4) & 0x7)+2 : 1;
	ch->pstack[ch->pstack_index].next_cmd_ptr += csz;
}

#if ATM_HAS_FX_GLISSANDO || ATM_HAS_FX_SLIDE

/* flags: bit 7 = 0 clamp, 1 wraparound */
static uint16_t slide_quantity(int8_t amount, int16_t value, int16_t bottom, int16_t top, uint8_t flags)
{
	const bool clamp = !(flags & 0x80);
	const int16_t res = value + amount;
	if (clamp) {
		if (res < bottom) {
			return bottom;
		} else if (res > top) {
			return top;
		}
	}
	return res;
}

#endif

#if ATM_HAS_FX_SLIDE

static void slidefx(struct atm_slide_params *slide_params, struct osc_params *osc_params)
{
	if (slide_params->slide_amount) {
		if ((slide_params->slide_count & 0x3F) >= (slide_params->slide_config & 0x3F)) {
			switch (slide_params->slide_count & 0xC0) {
#if ATM_HAS_FX_VOL_SLIDE
				case 0:
					osc_params->vol = slide_quantity(
											slide_params->slide_amount,
											osc_params->vol,
											0,
											MAX_VOLUME,
											slide_params->slide_config & 0x80);
					break;
#endif
#if ATM_HAS_FX_FREQ_SLIDE
				case 0x40:
					osc_params->phase_increment = slide_quantity(
													slide_params->slide_amount,
													osc_params->phase_increment,
													0,
													OSC_PHASE_INC_MAX,
													slide_params->slide_config & 0x80);
					break;
#endif
#if ATM_HAS_FX_MOD_SLIDE
				case 0x80:
					osc_params->mod = slide_quantity(
													slide_params->slide_amount,
													osc_params->mod,
													0,
													OSC_MOD_MAX,
													slide_params->slide_config & 0x80);
					break;
#endif
			}
			slide_params->slide_count &= 0xC0;
		} else {
			slide_params->slide_count++;
		}
	}
}
#endif

union fmt_hdr {
	uint16_t u16;
	struct {
		uint8_t fmt;
		uint8_t data;
	} f;
};

static const uint8_t *get_entry_pattern_array_ptr(const uint8_t *score)
{
	union fmt_hdr hdr;

	hdr.u16 = pgm_read_word(score);
	const uint8_t pattern_count = hdr.f.fmt & 0x02 ? hdr.f.data : 0;
	return hdr.f.fmt & 0x01 ? score + sizeof(uint16_t)*pattern_count + 3 : NULL;
}

static const uint8_t *get_track_start_ptr(struct atm_synth_state *score_state, const uint8_t track_index)
{
	const uint8_t *s = score_state->score_start;
	union fmt_hdr hdr;

	hdr.u16 = pgm_read_word(s);
	if (hdr.f.fmt & 0x02) {
		return s + pgm_read_word(s+2+sizeof(uint16_t)*track_index);
	}
	return hdr.f.fmt & 0x01 ? s+1+pgm_read_byte(hdr.f.data) : s+1;
}

void atm_synth_setup(void)
{
	osc_setup();
	/* no channel is active */
	atmlib_state.channel_active_mute = 0;
	/* take over all oscillators */
	for (unsigned n = 0; n < ARRAY_SIZE(channels); n++) {
		channels[n].dst_osc_params = &osc_params_array[n];
	}
}

static void atm_synth_init_channel(struct atm_channel_state *ch, struct osc_params *dst, struct atm_synth_state *player, uint8_t pattern_index)
{
	memset(ch, 0, sizeof(*ch));
	ch->mod = 0x7F;
	ch->dst_osc_params = dst;
	ch->pstack[0].next_cmd_ptr = get_track_start_ptr(player, pattern_index);
	ch->pstack[0].pattern_index = pattern_index;
}

static void atm_player_init_state(const uint8_t *score, struct atm_synth_state *dst)
{
	dst->score_start = score;
	dst->channel_active_mute |= 0b11110000;
	dst->tick_rate = 25;
}

void atm_synth_grab_channel(const uint8_t channel_index, struct osc_params *save)
{
	*save = osc_params_array[channel_index];
	memset(&osc_params_array[channel_index], 0, sizeof(osc_params_array[0]));
	channels[channel_index].dst_osc_params = save;
}

void atm_synth_release_channel(const uint8_t channel_index)
{
	osc_params_array[channel_index] = *channels[channel_index].dst_osc_params;
	channels[channel_index].dst_osc_params = &osc_params_array[channel_index];
}

void atm_synth_play_sfx_track(const uint8_t ch_index, const uint8_t *sfx, struct atm_sfx_state *sfx_state)
{
	atm_synth_stop_sfx_track(sfx_state);
	sfx_state->ch_index = ch_index;
	atm_synth_grab_channel(ch_index, &sfx_state->osc_params);
	atm_player_init_state((const uint8_t*)sfx, &sfx_state->track_info);
	/* override active flags so only one channel for is active for the SFX player */
	sfx_state->track_info.channel_active_mute = 1 << (ch_index+OSC_CH_COUNT);
	atm_synth_init_channel(&sfx_state->channel_state, &osc_params_array[ch_index], &sfx_state->track_info, 0);
	osc_set_tick_rate(1, sfx_state->track_info.tick_rate);
	/* Start SFX */
	osc_set_tick_callback(1, atm_synth_sfx_tick_handler, sfx_state);
}

void atm_synth_stop_sfx_track(struct atm_sfx_state *sfx_state)
{
	osc_set_tick_callback(1, NULL, NULL);
	atm_synth_release_channel(sfx_state->ch_index);
}

// stop playing
void atm_synth_stop_score(void) {
	osc_set_tick_callback(0, NULL, NULL);
}

void atm_synth_play_score(const uint8_t *score)
{
	/* stop current score if any */
	atm_synth_stop_score();
	/* Set default score data */
	atm_player_init_state(score, &atmlib_state);
	osc_set_tick_rate(0, atmlib_state.tick_rate);
	/* Read track count */
	const uint8_t *ep = get_entry_pattern_array_ptr(score);
	/* Fetch starting points for each track */
	for (unsigned n = 0; n < ARRAY_SIZE(channels); n++) {
		atm_synth_init_channel(&channels[n],
			channels[n].dst_osc_params, &atmlib_state, pgm_read_byte(&ep[n]));
	}
	/* Start playback */
	osc_set_tick_callback(0, atm_synth_score_tick_handler, NULL);
}

/* FIXME: the corresponding 'stop' function is missing */
void atm_synth_play_ext(const struct atm_synth_ext *synth_ext)
{
	/* stop current score if any */
	atm_synth_stop_score();
	/* Set default score data */
	atm_player_init_state(NULL, &atmlib_state);
	osc_set_tick_rate(0, atmlib_state.tick_rate);
	/* Read track count */
	/* Fetch starting points for each track */
	for (unsigned n = 0; n < ARRAY_SIZE(channels); n++) {
		atm_synth_init_channel(&channels[n],
			channels[n].dst_osc_params, &atmlib_state, 0);
	}
	/* Start playback */
	osc_set_tick_callback(0, atm_synth_ext_tick_handler, synth_ext);
}

uint8_t atm_synth_is_score_stopped(void)
{
	return !(atmlib_state.channel_active_mute & 0xF0);
}

uint8_t atm_synth_get_score_paused(void)
{
	if (!(atmlib_state.channel_active_mute & 0xF0)) {
		/* paused means it can resume */
		return 0;
	}
	osc_tick_callback cb;
	osc_get_tick_callback(0, &cb, NULL);
	return cb == NULL;
}

void atm_synth_set_score_paused(const uint8_t paused)
{
	if (!(atmlib_state.channel_active_mute & 0xF0)) {
		/* if the score is not ready to play do nothing */
		return;
	}
	for (unsigned n = 0; n < ARRAY_SIZE(channels); n++) {
		if (paused) {
			/* Volume for each channel should be saved here and restored upon unmute */
			/* but we want to save memory so after unpausing the fist note or effect */
			/* will update the volume again */
			channels[n].dst_osc_params->vol = 0;
		}
	}
	osc_set_tick_callback(0, paused ? NULL : atm_synth_score_tick_handler, NULL);
}

/* include source file directly so the compiler can inline static functions therein */
#include "cmd_parse.c"

static void process_fx(const uint8_t ch_index, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	(void)(score_state);

#if ATM_HAS_FX_NOISE_RETRIG
	// Noise retriggering
	if (ch_index == OSC_CH_THREE && ch->reConfig && (ch->reCount++ >= (ch->reConfig & 0x03))) {
		ch->dst_osc_params->phase_increment = note_index_2_phase_inc(ch->reConfig >> 2);
		ch->reCount = 0;
	}
#endif

#if ATM_HAS_FX_GLISSANDO
	//Apply Glissando
	if (ch->glisConfig && (ch->glisCount++ >= (ch->glisConfig & 0x7F))) {
		const uint8_t amount = (ch->glisConfig & 0x80) ? -1 : 1;
		const uint8_t note = slide_quantity(amount, ch->note, 1, LAST_NOTE, 0);
		ch->note = note;
		ch->dst_osc_params->phase_increment = note_index_2_phase_inc(note);
		ch->glisCount = 0;
	}
#endif

#if ATM_HAS_FX_SLIDE
	// Apply volume/frequency slides
	slidefx(&ch->vf_slide, ch->dst_osc_params);
#endif

#if ATM_HAS_FX_NOTE_RETRIG
	// Apply Arpeggio or Note Cut
	if (ch->arpNotes && ch->note) {
		if ((ch->arpCount & 0x1F) < (ch->arpTiming & 0x1F)) {
			ch->arpCount++;
		} else {
			if ((ch->arpCount & 0xE0) == 0x00) {
				ch->arpCount = 0x20;
			} else if ((ch->arpCount & 0xE0) == 0x20 && !(ch->arpTiming & 0x40) && (ch->arpNotes != 0xFF)) {
				ch->arpCount = 0x40;
			} else {
				ch->arpCount = 0x00;
			}
			uint8_t arpNote = ch->note;
			if ((ch->arpCount & 0xE0) != 0x00) {
				if (ch->arpNotes == 0xFF) {
					arpNote = 0;
				} else {
					arpNote += (ch->arpNotes >> 4);
				}
			}
			if ((ch->arpCount & 0xE0) == 0x40) {
				arpNote += (ch->arpNotes & 0x0F);
			}
			// Is it correct to add ch->trans_config to arpNote? The existing note should
			// already be transposed.
			ch->dst_osc_params->phase_increment = note_index_2_phase_inc(arpNote + ch->trans_config);
		}
	}
#endif

#if ATM_HAS_FX_LFO
	// Apply Tremolo or Vibrato
	if (ch->treviDepth) {
		int16_t vt = ((ch->treviConfig & 0x40) ? ch->dst_osc_params->phase_increment : ch->dst_osc_params->vol);
		vt = (ch->treviCount & 0x80) ? (vt + ch->treviDepth) : (vt - ch->treviDepth);
		if (vt < 0) {
			vt = 0;
		} else if (ch->treviConfig & 0x40) {
			if (vt > OSC_PHASE_INC_MAX) {
				vt = OSC_PHASE_INC_MAX;
			}
		} else if (!(ch->treviConfig & 0x40)) {
			if (vt > MAX_VOLUME) {
				vt = MAX_VOLUME;
			}
		}
		if (ch->treviConfig & 0x40) {
			ch->dst_osc_params->phase_increment = vt;
		} else {
			ch->dst_osc_params->vol = vt;
		}
		if ((ch->treviCount & 0x1F) < (ch->treviConfig & 0x1F)) {
			ch->treviCount++;
		} else {
			if (ch->treviCount & 0x80) {
				ch->treviCount = 0;
			} else {
				ch->treviCount = 0x80;
			}
		}
	}
#endif
}

static void process_channel(const uint8_t ch_index, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	process_fx(ch_index, score_state, ch);

	while (ch->delay == 0) {
		struct atm_cmd_data cmd;
		fetch_cmd(ch_index, ch, &cmd)
		log_cmd(ch_index, cmd.id, csz, cmd.params);
		process_cmd(ch_index, &cmd, score_state, ch);
	}

	if (ch->delay != 0xFFFF) {
		ch->delay--;
	}
}

static void atm_synth_ext_tick_handler(uint8_t cb_index, void *priv) {
	(void)(cb_index);
	struct atm_synth_ext *ext = (struct atm_synth_ext *)priv;

	for (uint8_t ch_index = 0; ch_index < ARRAY_SIZE(channels); ch_index++)
	{
		process_fx(ch_index, &atmlib_state, &channels[ch_index]);
		ext->cb(OSC_CH_COUNT, &atmlib_state, channels, ext);
		osc_set_tick_rate(0, atmlib_state.tick_rate);
	}
}

static void atm_synth_sfx_tick_handler(uint8_t cb_index, void *priv) {
	(void)(cb_index);
	struct atm_sfx_state *sfx_state = (struct atm_sfx_state *)priv;

	const uint8_t sfx_ch_index = sfx_state->ch_index;
	process_channel(sfx_ch_index, &sfx_state->track_info, &sfx_state->channel_state);
	osc_set_tick_rate(1, sfx_state->track_info.tick_rate);
	if (!(sfx_state->track_info.channel_active_mute & 0xF0)) {
		/* sfx done */
		atm_synth_stop_sfx_track(sfx_state);
	}
}

static void atm_synth_score_tick_handler(uint8_t cb_index, void *priv) {
	(void)(cb_index);
	(void)(priv);
	// for every channel start working
	for (uint8_t ch_index = 0; ch_index < ARRAY_SIZE(channels); ch_index++)
	{
		process_channel(ch_index, &atmlib_state, &channels[ch_index]);
		osc_set_tick_rate(0, atmlib_state.tick_rate);
	}

	/* if all channels are inactive, stop playing or check for repeat */
	if (!(atmlib_state.channel_active_mute & 0xF0)) {
		for (uint8_t k = 0; k < ARRAY_SIZE(channels); k++) {
			struct atm_channel_state *const ch = &channels[k];
			/* a quirk in the original implementation does not allow to loop to pattern 0 */
			if (!ch->loop_pattern_index) {
				continue;
			}
			pattern_cmd_ptr(ch) = get_track_start_ptr(&atmlib_state, ch->loop_pattern_index);
			ch->delay = 0;
			atmlib_state.channel_active_mute |= (1<<(k+OSC_CH_COUNT));
		}
		if (!(atmlib_state.channel_active_mute & 0xF0)) {
			atm_synth_stop_score();
		}
	}
}
