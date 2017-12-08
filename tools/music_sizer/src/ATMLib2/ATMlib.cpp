
#include "ATMlib.h"


void ATMsynth::setup(void) {
	if (!setup_done) {
		atm_synth_setup();
		setup_done = true;
	}
}

void ATMsynth::play(const uint8_t *score) {
	setup();
	atm_synth_play_score(score);
}

// Stop playing, unload melody
void ATMsynth::stop() {
	atm_synth_stop_score();
}

// Start grinding samples or Pause playback
void ATMsynth::playPause() {
	atm_synth_set_score_paused(!atm_synth_get_score_paused());
}
