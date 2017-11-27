#include "Game.h"

#ifdef ENABLE_AUDIO
#include "src/ATMLib2/ATMlib.h"
// Todo change to <ATMLib.h> once we publish
#include "sound/song.h"

struct atm_sfx_state sfx_state;
void Sound::init() {
  // Initialize audio system
  arduboy.audio.on();

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
