#include "Game.h"

#ifdef ENABLE_AUDIO
#include <Arduboy2Audio.h>
static Arduboy2Audio audio;


#include "src/ATMLib2/ATMlib.h"
// Todo change to <ATMLib.h> once we publish
#include "sound/SFX.h"
#include "sound/evade2_00_intro.h"
#include "sound/evade2_01_stage_1.h"
#include "sound/evade2_03_stage_2.h"

struct atm_sfx_state sfx_state;
void Sound::init() {
  // Initialize audio system
  audio.begin();
  audio.on();

  // Initialize ATMLib2
  atm_synth_setup();
}

void Sound::play_sound(BYTE id) {
  switch (id) {
    case FIRE_SOUND:
      // Play SFX
      atm_synth_play_sfx_track(OSC_CH_TWO, (const uint8_t *)&pew, &sfx_state);
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
  atm_synth_stop_score();
}

void Sound::play_score(BYTE id) {
  // return;
  switch (id) {
    case INTRO_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_00_intro);
      break;
    case STAGE_1_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_01_stage1);
      break; 
    case STAGE_2_SONG:
      atm_synth_play_score((const uint8_t *)&evade2_03_stage2);
      break;           
    default: 
      atm_synth_play_score((const uint8_t *)&evade2_00_intro);
    break;
  }
}
#else
void Sound::init() {}
void Sound::play_sound(BYTE id) {}
void Sound::play_score(BYTE id) {}
void Sound::stfu() {}
#endif
