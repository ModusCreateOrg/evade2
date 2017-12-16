#define DEBUGME
#include "Evade2.h"

#ifdef ENABLE_AUDIO
#include <Arduboy2Audio.h>
static Arduboy2Audio audio;

#include "src/ATMLib2/ATMlib.h"

// Todo change to <ATMLib.h> once we publish
#include "sound/SFX.h"
// #include "sound/evade2_00_intro.h"
#include "sound/evade2_00_intro_alt_smaller.h"
#include "sound/evade2_01_stage_1_alt_smaller.h"
#include "sound/evade2_02_stage_1_boss.h"
#include "sound/evade2_03_stage_2_alt_smaller.h"
#include "sound/evade2_04_stage_2_boss.h"

#include "sound/evade2_05_stage_3.h"
#include "sound/evade2_06_stage_3_boss.h"

#include "sound/evade2_10_game_over.h"
#include "sound/evade2_11_get_ready.h"

BYTE current_song = -1;

struct atm_sfx_state sfx_state;
void Sound::init() {
  // Initialize audio system
  audio.on();

  // Initialize ATMLib2
  atm_synth_setup();
}

// Prioritize sfx by channel.
// Ch 0 - UNUSED (Music trebel)
// Ch 1 - Player Shoot
// Ch 2 - Enemy Shoot
// Ch 3 - Player hit by enemy (noise)
void Sound::play_sound(BYTE id) {
  static const PROGMEM UBYTE *const sounds[] = {
    (UBYTE *)&SFX_player_shoot,
    (UBYTE *)&SFX_enemy_shoot,
    (UBYTE *)&SFX_player_hit,
  };

  atm_synth_stop_sfx_track(&sfx_state);
  atm_synth_play_sfx_track(OSC_CH_ONE, pgm_read_word(&sounds[id]), &sfx_state);
}

// TODO: getSize() a temp function that is only meant to be
//       used for development to allow us to determine the size
//       of a particular score and will be removed before launch.
long Sound::getSize() {
  return 0;
  // return sizeof(score);
}

// Shut down audio
void Sound::stfu() {
  current_song = -1;
  atm_synth_stop_score();
}

void Sound::play_score(BYTE id) {
  static const PROGMEM UBYTE *const songs[] = {
    (UBYTE *)&evade2_00_intro_alt_smaller,   // 0 INTRO_SONG
    (UBYTE *)&evade2_01_stage_1_alt_smaller, // 1 STAGE_1_SONG
    (UBYTE *)&evade2_02_stage_1_boss,        // 2 STAGE_1_BOSS_SONG
    (UBYTE *)&evade2_03_stage_2_alt_smaller, // 3 STAGE_2_SONG
    (UBYTE *)&evade2_04_stage_2_boss,        // 4 STAGE_2_BOSS_SONG
    (UBYTE *)&evade2_05_stage_3,             // 5 STAGE_3_SONG
    (UBYTE *)&evade2_06_stage_3_boss,        // 6 STAGE_3_BOSS_SONG
    (UBYTE *)&evade2_10_game_over,           // 7 GAME_OVER_SONG
    (UBYTE *)&evade2_11_get_ready,           // 8 GET_READY_SONG
  };

  if (current_song == id) {
    return;
  }

  atm_synth_play_score(pgm_read_word(&songs[id]));
  current_song = id;
}
#else
void Sound::init() {}
void Sound::play_sound(BYTE id) {}
void Sound::play_score(BYTE id) {}
void Sound::stfu() {}
#endif
