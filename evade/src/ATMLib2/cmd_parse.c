
/* compile only when included by atm_synth.c */
#ifdef ATM_PATTERN_STACK_DEPTH

#include "atm_cmd_constants.h"

static void cmd_note(const uint8_t note, struct atm_channel_state *ch)
{
	ch->note = note ? note + ch->trans_config : note;
	ch->dst_osc_params->phase_increment = note_index_2_phase_inc(ch->note);
	ch->dst_osc_params->vol = note ? ch->vol : 0;
	ch->dst_osc_params->mod = ch->mod;	
}

static void process_immediate_cmd(const uint8_t ch_index, const uint8_t cmd_id, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
/* Immediate commands */
	(void)(ch_index);
	switch (cmd_id) {
#if ATM_HAS_FX_GLISSANDO
		case ATM_CMD_I_GLISSANDO_OFF:
			ch->glisConfig = 0;
			break;
#endif

#if ATM_HAS_FX_ARPEGGIO
		case ATM_CMD_I_ARPEGGIO_OFF:
			ch->arpNotes = 0;
			break;
#endif

#if ATM_HAS_FX_NOTECUT
		case ATM_CMD_I_NOTECUT_OFF:
			ch->arpNotes = 0;
			break;
#endif

#if ATM_HAS_FX_NOISE_RETRIG
		case ATM_CMD_I_NOISE_RETRIG_OFF:
			ch->reConfig = 0;
			break;
#endif

		case ATM_CMD_I_STOP:
			goto stop_channel;
		case ATM_CMD_I_RETURN:
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
		case ATM_CMD_I_TRANSPOSITION_OFF:
			ch->trans_config = 0;
			break;
	}
	return;

stop_channel:
	score_state->channel_active_mute = score_state->channel_active_mute ^ (1 << (ch_index + OSC_CH_COUNT));
	ch->dst_osc_params->vol = 0;
	ch->delay = 0xFFFF;
}

static void process_parametrised_cmd(const uint8_t ch_index, const struct atm_cmd_data *cmd, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	(void)(ch_index);
	/* Parametrised commands */

	const uint8_t csz = ((cmd->id >> 4) & 0x7)+1;

	switch (cmd->id & 0x0F) {
		case ATM_CMD_ID_CALL:
			/* ignore call command if the stack is full */
			if (ch->pstack_index < ATM_PATTERN_STACK_DEPTH-1) {
				uint8_t new_track = cmd->params[0];
				uint8_t new_counter = csz > 1 ? cmd->params[1] : 0;
				if (new_track != pattern_index(ch)) {
					/* push new pattern on stack */
					ch->pstack_index++;
					pattern_index(ch) = new_track;
				}
				pattern_repetition_counter(ch) = new_counter;
			}
			/* if the stack is full and we cannot call, the start of the current pattern will be fetched */
			pattern_cmd_ptr(ch) = get_track_start_ptr(score_state, pattern_index(ch));
			break;

#if ATM_HAS_FX_GLISSANDO
		case ATM_CMD_ID_GLISSANDO_ON:
			ch->glisConfig = cmd->params[0];
			ch->glisCount = 0;
			break;
#endif

#if ATM_HAS_FX_ARPEGGIO
		case ATM_CMD_ID_ARPEGGIO_ON:
			ch->arpNotes = cmd->params[0];
			ch->arpTiming = cmd->params[1];
			break;
#endif

#if ATM_HAS_FX_NOTECUT
		case ATM_CMD_ID_NOTECUT_ON:
			ch->arpNotes = 0xFF;
			ch->arpTiming = cmd->params[0];
			break;
#endif

#if ATM_HAS_FX_NOISE_RETRIG
		case ATM_CMD_ID_NOISE_RETRIG_ON:
			ch->reConfig = cmd->params[0];
			ch->reCount = 0;
			break;
#endif

		case ATM_CMD_ID_SET_TRANSPOSITION:
			ch->trans_config = cmd->params[0];
			break;
		case ATM_CMD_ID_ADD_TRANSPOSITION:
			ch->trans_config += (int8_t)cmd->params[0];
			break;
		case ATM_CMD_ID_SET_TEMPO:
			score_state->tick_rate = cmd->params[0];
			break;
		case ATM_CMD_ID_ADD_TEMPO:
			score_state->tick_rate += (int8_t)cmd->params[0];
			break;
		case ATM_CMD_ID_SET_VOLUME:
		{
			const uint8_t vol = cmd->params[0];
			ch->vol = vol;
			ch->dst_osc_params->vol = vol;
			break;
		}
		case ATM_CMD_ID_SET_MOD:
		{
			const uint8_t mod = cmd->params[0];
			ch->mod = mod;
			ch->dst_osc_params->mod = mod;
			break;
		}
		case ATM_CMD_ID_SET_LOOP_PATTERN:
			ch->loop_pattern_index = cmd->params[0];
			break;

#if ATM_HAS_FX_SLIDE
		case ATM_CMD_ID_SLIDE:
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
			break;
#endif

#if ATM_HAS_FX_LFO
		case ATM_CMD_ID_LFO:
			/* b------pp s = pp = param: vol, freq, mod */
			if (csz > 1) {
				/* FX on */
				ch->treviDepth = cmd->params[1];
				ch->treviConfig = cmd->params[2] | (cmd->params[0] << 6);
				ch->treviCount = 0;
			} else {
				/* FX off */
				ch->treviDepth = 0;
			}
			break;
#endif

		case ATM_CMD_ID_LONG_DELAY:
			ch->delay = csz > 1 ? (cmd->params[0]<<8)|cmd->params[1] : cmd->params[0];
			ch->delay += 1;
			break;
	}
}

static void process_cmd(const uint8_t ch_index, const struct atm_cmd_data *cmd, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	if (cmd->id < 64) {
		/* 0 … 63 : NOTE ON/OFF */
		cmd_note(cmd->id, ch);

#if ATM_HAS_FX_NOTE_RETRIG
		/* ARP retriggering */
		if (ch->arpTiming & 0x20) {
			ch->arpCount = 0;
		}
#endif
		return;
	}

	/* Cmd type is the 3 MSBs */
	const uint8_t type = cmd->id & 0xE0;
	if (type == 0x40) {
		/* delay */
		ch->delay = (cmd->id & 0x3F)+1;
	} else if (type == 0x60) {
		/* immediate */
		process_immediate_cmd(ch_index, cmd->id, score_state, ch);
	} else if (type & 0x80) {
		process_parametrised_cmd(ch_index, cmd, score_state, ch);
	}
}

void ext_synth_command(const uint8_t ch_index, const struct atm_cmd_data *cmd, struct atm_synth_state *score_state, struct atm_channel_state *ch)
{
	process_cmd(ch_index, cmd, score_state, ch);
}
#endif
