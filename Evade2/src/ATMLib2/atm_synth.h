
#include <stddef.h>
#include <stdint.h>

#include "osc.h"
#include "atm_cmd_constants.h"

/* Adjust the following to reduce memory usage */

#define ATM_PATTERN_STACK_DEPTH (3)

/* Disable all FX to save space */
#define ATM_HAS_FX_NONE (0)

#if ATM_HAS_FX_NONE
#define ATM_HAS_FX_NOISE_RETRIG (0)
#define ATM_HAS_FX_NOTE_RETRIG (0)
#define ATM_HAS_FX_SLIDE (0)
#define ATM_HAS_FX_LFO (0)
#define ATM_HAS_FX_GLISSANDO (0)
#define ATM_HAS_FX_LOOP (0)
#else
#define ATM_HAS_FX_NOISE_RETRIG (1)
#define ATM_HAS_FX_NOTE_RETRIG (1)
#define ATM_HAS_FX_SLIDE (1)
#define ATM_HAS_FX_LFO (0)
#define ATM_HAS_FX_GLISSANDO (0)
#define ATM_HAS_FX_LOOP (1)
#endif

/* Public API - we will try not to break this, no promises! */

#define ATM_SCORE_FMT_MINIMAL_MONO (0x0)
#define ATM_SCORE_FMT_FULL_MONO (0x2)
#define ATM_SCORE_FMT_FULL (0x3)

struct atm_synth_state;
struct atm_sfx_state;
struct atm_channel_state;
struct atm_synth_ext;
struct atm_cmd_data;

typedef void (*atm_synth_ext_callback)(const uint8_t channel_count, struct atm_synth_state *synth_state, struct atm_channel_state *ch, struct atm_synth_ext *synth_ext);

struct atm_synth_ext {
	atm_synth_ext_callback cb;
	void *priv;
};

void atm_synth_setup(void);

void atm_synth_play_score(const uint8_t *score);
void atm_synth_stop_score(void);
uint8_t atm_synth_is_score_stopped(void);

void atm_synth_set_score_paused(const uint8_t paused);
uint8_t atm_synth_get_score_paused(void);

void atm_synth_grab_channel(const uint8_t channel_index, struct osc_params *save);
void atm_synth_release_channel(const uint8_t channel_index);

void atm_synth_play_ext(const struct atm_synth_ext *synth_ext);
void ext_synth_command(const uint8_t ch_index, const struct atm_cmd_data *cmd, struct atm_synth_state *score_state, struct atm_channel_state *ch);

/* Play score as a sound effect on channel_index

Music playback (if any) is muted on channel_index for the duration of sound
effect playback and resumes when the sound effect is stopped or ran its course.

It is possible to start playback of a new sound effect while one is already
being played back, the active sound effect will stop and the new one will replace it.

Sound effect scores must be in ATM_SCORE_FMT_MINIMAL_MONO or ATM_SCORE_FMT_FULL_MONO format.
*/
void atm_synth_play_sfx_track(const uint8_t channel_index, const uint8_t *score,  struct atm_sfx_state *sfx_state);

/* Stop a previously started sound effect score */
void atm_synth_stop_sfx_track(struct atm_sfx_state *sfx_state);

/* Check if a sound effect score is active */
uint8_t atm_synth_is_sfx_stopped(struct atm_sfx_state *sfx_state);

/* Private structures - anything beyond this point is considered internal to the library

structs are only made available in this file so clients can allocate them statically.
All fields shoudl be considered private.

If you think you have a valid use case for exposing some feature please
get in touch with the maintainers.

*/

struct atm_synth_state {
	const uint8_t *score_start;
	uint8_t tick_rate;
	uint8_t channel_active_mute; //0b11110000;
	//                               ||||||||
	//                               |||||||└->  0  channel 0 is muted (0 = false / 1 = true)
	//                               ||||||└-->  1  channel 1 is muted (0 = false / 1 = true)
	//                               |||||└--->  2  channel 2 is muted (0 = false / 1 = true)
	//                               ||||└---->  3  channel 3 is muted (0 = false / 1 = true)
	//                               |||└----->  4  channel 0 is Active (0 = false / 1 = true)
	//                               ||└------>  5  channel 1 is Active (0 = false / 1 = true)
	//                               |└------->  6  channel 2 is Active (0 = false / 1 = true)
	//                               └-------->  7  channel 3 is Active (0 = false / 1 = true)
};

#if ATM_HAS_FX_SLIDE

struct atm_slide_params {
	int8_t slide_amount;
	uint8_t slide_config;
	uint8_t slide_count;
};

#endif

struct atm_pattern_state {
	const uint8_t *next_cmd_ptr;
	uint8_t pattern_index;
	uint8_t repetitions_counter;
};

struct atm_channel_state {
	uint8_t note;
	uint8_t vol;
	uint8_t mod;
	uint16_t delay;
	// Transposition FX
	int8_t trans_config;

	// Nesting
	struct atm_pattern_state pstack[ATM_PATTERN_STACK_DEPTH];
	uint8_t pstack_index;
#if ATM_HAS_FX_LOOP
	uint8_t loop_pattern_index;
#endif

	struct osc_params *dst_osc_params;

#if ATM_HAS_FX_SLIDE
	// Volume & Frequency slide FX
	struct atm_slide_params vf_slide;
#endif

#if ATM_HAS_FX_NOTE_RETRIG
	// Arpeggio or Note Cut FX
	uint8_t arpNotes;       // notes: base, base+[7:4], base+[7:4]+[3:0], if FF => note cut ON
	uint8_t arpTiming;      // [7] = reserved, [6] = not third note ,[5] = retrigger, [4:0] = tick count
	uint8_t arpCount;
#endif

#if ATM_HAS_FX_NOISE_RETRIG
	// Retrig FX
	uint8_t reConfig;       // [7:2] = , [1:0] = speed // used for the noise channel
	uint8_t reCount;
#endif

#if ATM_HAS_FX_LFO
	// Tremolo or Vibrato FX
	uint8_t treviDepth;
	uint8_t treviConfig;
	uint8_t treviCount;
#endif

#if ATM_HAS_FX_GLISSANDO
	// Glissando FX
	int8_t glisConfig;
	uint8_t glisCount;
#endif
};

struct atm_sfx_state {
	uint8_t ch_index;
	struct atm_synth_state track_info;
	struct atm_channel_state channel_state;
	struct osc_params osc_params;
};

struct atm_cmd_data {
	uint8_t id;
	uint8_t params[3];
};
