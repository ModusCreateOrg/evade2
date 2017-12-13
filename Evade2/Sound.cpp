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

#include "sound/evade2_07_stage_4.h"
#include "sound/evade2_08_stage_4_boss.h"

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
  atm_synth_stop_sfx_track(&sfx_state);

  switch (id) {
    case SFX_PLAYER_SHOOT:
      atm_synth_play_sfx_track(OSC_CH_ONE, (const uint8_t *)&SFX_player_shoot, &sfx_state);
      break;
    case SFX_ENEMY_SHOOT:
      atm_synth_play_sfx_track(OSC_CH_ONE, (const uint8_t *)&SFX_enemy_shoot, &sfx_state);
      break;
    case SFX_PLAYER_HIT_BY_ENEMY:
      atm_synth_play_sfx_track(OSC_CH_ONE, (const uint8_t *)&SFX_player_hit, &sfx_state);
      break;
  }
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

  if (current_song == id) {
    return;
  }
  // return;
  switch (id) {
    case INTRO_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_00_intro_alt_smaller);
      break;
    case STAGE_1_SONG:
      // atm_synth_play_score((const uint8_t *)&evade2_01_stage_1);
      atm_synth_play_score((const uint8_t *)&evade2_01_stage_1_alt_smaller);
    
      break;     
    case STAGE_1_BOSS_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_02_stage_1_boss);
      break; 
    case STAGE_2_SONG:
      // atm_synth_play_score((const uint8_t *)&evade2_03_stage_2);
      atm_synth_play_score((const uint8_t *)&evade2_03_stage_2_alt_smaller);
      break;    
    case STAGE_2_BOSS_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_04_stage_2_boss);
      break; 
    case STAGE_3_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_05_stage_3);
      break;           
    case STAGE_3_BOSS_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_06_stage_3_boss);
      break;
    // case STAGE_4_SONG:
    //   atm_synth_play_score((const uint8_t *)&evade2_07_stage_4);
    //   break;
    // case STAGE_4_BOSS_SONG:
    //   atm_synth_play_score((const uint8_t *)&evade2_08_stage_4_boss);
    //   break;

    case GAME_OVER_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_10_game_over);
      break;                     
    case GET_READY_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_11_get_ready);
      break;
    default: 
      atm_synth_play_score((const uint8_t *)&evade2_00_intro_alt_smaller);
    break;
  }

  current_song = id;
}
#else
void Sound::init() {}
void Sound::play_sound(BYTE id) {}
void Sound::play_score(BYTE id) {}
void Sound::stfu() {}
#endif
