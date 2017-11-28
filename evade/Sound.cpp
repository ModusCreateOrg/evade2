#include "Game.h"

/*
Pre-change
Sketch uses 18,348 bytes (63%) of program storage space. Maximum is 28,672 bytes.
Global variables use 1,860 bytes (72%) 

Post-Change
ketch uses 18,050 bytes (62%) of program storage space. Maximum is 28,672 bytes.
Global variables use 1,845 bytes (72%) of dynamic memory, leaving 715 bytes for local variables. Maximum is 2,560 bytes.

*/
#ifdef ENABLE_AUDIO
#include <Arduboy2Audio.h>
static Arduboy2Audio audio;


#include "src/ATMLib2/ATMlib.h"
// Todo change to <ATMLib.h> once we publish
#include "sound/song.h"

struct atm_sfx_state sfx_state;
void Sound::init() {
  // Initialize audio system
  audio.begin();
  audio.on();

  // Initialize ATMLib2
  atm_synth_setup();
}

void Sound::play_sound(int id) {
  switch (id) {
    case FIRE_SOUND:
      // Play SFX
      atm_synth_play_sfx_track(OSC_CH_TWO, (const uint8_t *)&pew, &sfx_state);
      break;
  }
}

void Sound::play_score(int id) {
  // return;
  switch (id) {
    case DEMO_SCORE:
      // Play a song
      atm_synth_play_score((const uint8_t *)&score);
      break;
  }
}
#else
void Sound::init() {}
void Sound::play_sound(int id) {}
void Sound::play_score(int id) {}
#endif
