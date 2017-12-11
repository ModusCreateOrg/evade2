
/* compile only when included by atm_synth.c */
#ifdef ATM_PATTERN_STACK_DEPTH

#include "atm_cmd_constants.h"

static void trigger_note(const uint8_t note, struct atm_channel_state *ch)
{
	ch->dst_osc_params->phase_increment = note_index_2_phase_inc(note + ch->trans_config);
	if (!note) {
		ch->dst_osc_params->vol = 0;
	} else {
#if ATM_HAS_FX_SLIDE
		if (!ch->vf_slide.slide_amount) {
			/* No slide */
			goto trigger_both;
		} else if (ch->vf_slide.slide_config & 0x40) {
			/* Slide is re-triggered */
			ch->vf_slide.slide_count &= 0x3F;
			goto trigger_both;
		} else {
			/* Slide is not re-triggered */
			const uint8_t q = ch->vf_slide.slide_count & 0xC0;
			if (!q == 0) {
				/* Vol slide, don't trigger vol */
				ch->dst_osc_params->mod = ch->mod;
			} else if (q == 0x80) {
				/* Mod slide, don't trigger mod */
				ch->dst_osc_params->vol = ch->vol;
			} else {
				goto trigger_both;
			}
		}
		return;
#else
		goto trigger_both;
#endif
	}

trigger_both:
	ch->dst_osc_params->vol = ch->vol;
	ch->dst_osc_params->mod = ch->mod;
}

static void process_immediate_cmd(const uint8_t ch_index, const uint8_t cmd_id, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	const enum atm_immediate_cmd_constants cid = cmd_id;

	/* Immediate commands */
	switch (cid) {

		case ATM_CMD_I_TRANSPOSITION_OFF:
			ch->trans_config = 0;
			break;

		case ATM_CMD_I_PATTERN_END:
			if (pattern_repetition_counter(ch) > 0) {
				/* Repeat track */
				pattern_repetition_counter(ch)--;
				pattern_cmd_ptr(ch) = get_track_start_ptr(score_state, pattern_index(ch));
			} else {
				/* Check stack depth */
				if (ch->pstack_index == 0) {
					goto stop_channel;
				} else {
					/* pop stack */
					ch->pstack_index--;
				}
			}
			break;

		case ATM_CMD_I_GLISSANDO_OFF:
#if ATM_HAS_FX_GLISSANDO
			ch->glisConfig = 0;
#endif
			break;


		case ATM_CMD_I_ARPEGGIO_OFF:
#if ATM_HAS_FX_NOTE_RETRIG
			ch->arpCount = 0x80;
#endif
			break;

		case ATM_CMD_I_NOISE_RETRIG_OFF:
#if ATM_HAS_FX_NOISE_RETRIG
			ch->reConfig = 0;
#endif
			break;
	}
	return;

stop_channel:
	score_state->channel_active_mute = score_state->channel_active_mute ^ (1 << (ch_index + OSC_CH_COUNT));
	ch->dst_osc_params->vol = 0;
	ch->delay = 0xFFFF;
}

static void process_1p_cmd(const struct atm_cmd_data *cmd, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	const enum atm_single_byte_cmd_id_constants cid = cmd->id;

	switch (cid) {
		case ATM_CMD_1P_NOISE_RETRIG_ON:
#if ATM_HAS_FX_NOISE_RETRIG
			ch->reConfig = cmd->params[0];
			ch->reCount = 0;
#endif
			break;

		case ATM_CMD_1P_SET_TRANSPOSITION:
			ch->trans_config = cmd->params[0];
			break;

		case ATM_CMD_1P_ADD_TRANSPOSITION:
			ch->trans_config += (int8_t)cmd->params[0];
			break;

		case ATM_CMD_1P_SET_TEMPO:
			score_state->tick_rate = cmd->params[0];
			break;

		case ATM_CMD_1P_ADD_TEMPO:
			score_state->tick_rate += (int8_t)cmd->params[0];
			break;

		case ATM_CMD_1P_SET_VOLUME:
		{
			const uint8_t vol = cmd->params[0];
			ch->vol = vol;
			ch->dst_osc_params->vol = vol;
			break;
		}

		case ATM_CMD_1P_SET_MOD:
		{
			const uint8_t mod = cmd->params[0];
			ch->mod = mod;
			ch->dst_osc_params->mod = mod;
			break;
		}
	}
}

static void process_np_cmd(const struct atm_cmd_data *cmd, const uint8_t csz, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	const enum atm_parametrised_cmd_id_constants cid = cmd->id & 0x0F;

	/* Parametrised commands */
	switch (cid) {
		case ATM_CMD_NP_CALL:
			/* ignore call command if the stack is full */
			if (ch->pstack_index < ATM_PATTERN_STACK_DEPTH-1) {
				const uint8_t new_track = cmd->params[0];
				if (new_track != pattern_index(ch)) {
					const uint8_t new_counter = csz > 1 ? cmd->params[1] : 0;
					/* push new pattern on stack */
					ch->pstack_index++;
					pattern_index(ch) = new_track;
					pattern_repetition_counter(ch) = new_counter;
					pattern_cmd_ptr(ch) = get_track_start_ptr(score_state, pattern_index(ch));
				}
			}
			/* if the stack is full and we cannot call, skip the call command */
			break;

		case ATM_CMD_NP_GLISSANDO_ON:
#if ATM_HAS_FX_GLISSANDO
			ch->glisConfig = cmd->params[0];
			ch->glisCount = 0;
#endif
			break;

		case ATM_CMD_NP_ARPEGGIO_ON:
#if ATM_HAS_FX_NOTE_RETRIG
			ch->arpTiming = cmd->params[0];
			/* arpeggio or notecut */
			ch->arpNotes = csz > 1 ? cmd->params[1] : 0xFF;
			ch->arpCount = 0x00;
#endif
			break;

		case ATM_CMD_NP_SET_LOOP_PATTERN:
#if ATM_HAS_FX_LOOP
			ch->loop_pattern_index = cmd->params[0];
#endif
			break;

		case ATM_CMD_NP_SLIDE:
#if ATM_HAS_FX_SLIDE
			/* b------pp s = pp = param: vol, freq, mod */
			if (csz > 1) {
				/* FX on */
				ch->vf_slide.slide_count = cmd->params[0] << 6;
				ch->vf_slide.slide_amount = (int8_t)cmd->params[1];
				ch->vf_slide.slide_config = csz > 2 ? cmd->params[2] : 0;
			} else {
				/* FX off */
				ch->vf_slide.slide_amount = 0;
			}
#endif
			break;

		case ATM_CMD_NP_LFO:
#if ATM_HAS_FX_LFO
			/* b------pp s = pp = param: vol, freq, mod */
			if (csz > 1) {
				/* FX on */
				ch->treviDepth = cmd->params[1];
				ch->treviConfig = cmd->params[2] | (cmd->params[0] << 6);
				/* Effect starts from center point so it must run for 1/4 period
				   before changing sign. params[2] carries half period so div by 2
				*/
				ch->treviCount = (cmd->params[2] & 0x1F) >> 1;
			} else {
				/* FX off */
				ch->treviDepth = 0;
				/* This effect does not reset volume, pitch or mod to the center
				   value in case it is not interrupted on a period boundary.
				   Fixing this costs ~ +30 bytes of code so I'm calling it a
				   feature for the time being.
				trigger_note(ch->note, ch);
				*/
			}
#endif
			break;

		case ATM_CMD_NP_LONG_DELAY:
			ch->delay = csz > 1 ? (cmd->params[0]<<8)|cmd->params[1] : cmd->params[0];
			ch->delay += 1;
			break;
	}
}

static void process_cmd(const uint8_t ch_index, const struct atm_cmd_data *cmd, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	const uint8_t **next_cmd_ptr = &pattern_cmd_ptr(ch);
	*next_cmd_ptr += 1;

	if (cmd->id < ATM_CMD_BLK_DELAY) {
		/* 0 … 63 : NOTE ON/OFF */
		ch->note = cmd->id;
		trigger_note(cmd->id, ch);

#if ATM_HAS_FX_NOTE_RETRIG
		/* ARP retriggering */
		if (ch->arpTiming & 0x20) {
			ch->arpCount = 0;
		}
#endif
	} else if (cmd->id < ATM_CMD_BLK_IMMEDIATE) {
		/* delay */
		ch->delay = cmd->id - 63;
	} else if (cmd->id < ATM_CMD_BLK_1_PARAMETER) {
		/* immediate */
		/* process_immediate_cmd() can modify next_cmd_ptr so increase it first */
		process_immediate_cmd(ch_index, cmd->id, score_state, ch);
	} else if (cmd->id < ATM_CMD_BLK_N_PARAMETER) {
		/* 1 parameter byte command */
		*next_cmd_ptr += 1;
		process_1p_cmd(cmd, score_state, ch);
	} else {
		const uint8_t csz = ((cmd->id >> 4) & 0x07) + 1;
		/* n parameter byte command */
		*next_cmd_ptr += csz;
		/* process_np_cmd() can modify next_cmd_ptr so increase it first */
		process_np_cmd(cmd, csz, score_state, ch);
	}
}

void ext_synth_command(const uint8_t ch_index, const struct atm_cmd_data *cmd, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	process_cmd(ch_index, cmd, score_state, ch);
}
#endif
