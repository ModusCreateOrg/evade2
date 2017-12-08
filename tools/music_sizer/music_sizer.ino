#include <Arduboy2.h>

#include "src/ATMLib2/ATMLib.h"

#include "Types.h"
#include "sound/SFX.h"
#include "sound/evade2_00_intro.h"
#include "sound/evade2_01_stage_1.h"
#include "sound/evade2_02_stage_1_boss.h"
#include "sound/evade2_03_stage_2.h"
#include "sound/evade2_04_stage_2_boss.h"

#include "sound/evade2_06_stage_3_boss.h"
#include "sound/evade2_10_game_over.h"

Arduboy2 arduboy;

void setup() {
  // put your setup code here, to run once:
  arduboy.boot();  
  // Initialize audio system
  arduboy.audio.begin();
  arduboy.audio.on();

  // Initialize ATMLib2
  atm_synth_setup();
  arduboy.setFrameRate(5);
}


const char* songStrings[7] = {
  "evade2_00_intro",
  "evade2_01_stage_1",
  "evade2_02_stage_1_boss",
  "evade2_03_stage_2",
  "evade2_04_stage_2_boss",
  "evade2_06_stage_3_boss",
  "evade2_10_game_over",
};

int i = 0,
    playingIndex = -1;

void loop() {
  if (! arduboy.nextFrame()) {
    return;
  }
  arduboy.clear();
  arduboy.setTextSize(1);

  arduboy.setCursor(0,0);
  uint8_t songRef;
  arduboy.print(songStrings[i]);
  arduboy.setCursor(0,10);

  if (i > 6) {
    i = 0;
  }
  else if (i < 0) {
    i = 6;
  }
  
  if (arduboy.pressed(UP_BUTTON)) {
    i++;
  }
  else if (arduboy.pressed(DOWN_BUTTON)) {
    i--;
  }

  if (i == 0) {
    arduboy.print(sizeof(evade2_00_intro));
    if (playingIndex != i) {
      playingIndex = i;
      atm_synth_play_score((const uint8_t *)&evade2_00_intro);
    }
  }
  else if (i == 1) {
    arduboy.print(sizeof(evade2_01_stage_1));
    if (playingIndex != i) {
      playingIndex = i;
      atm_synth_play_score((const uint8_t *)&evade2_01_stage_1);
    }
  }
  else if (i == 2) {
    arduboy.print(sizeof(evade2_02_stage_1_boss));
    if (playingIndex != i) {
      playingIndex = i;
      atm_synth_play_score((const uint8_t *)&evade2_02_stage_1_boss);
    }
  }
  else if (i == 3) {
    arduboy.print(sizeof(evade2_03_stage_2));
    if (playingIndex != i) {
      playingIndex = i;
      atm_synth_play_score((const uint8_t *)&evade2_03_stage_2);
    }
  }
  else if (i == 4) {
    arduboy.print(sizeof(evade2_04_stage_2_boss));
    if (playingIndex != i) {
      playingIndex = i;
      atm_synth_play_score((const uint8_t *)&evade2_04_stage_2_boss);
    }
  }
  else if (i == 5) {
    arduboy.print(sizeof(evade2_06_stage_3_boss));
    if (playingIndex != i) {
      playingIndex = i;
      atm_synth_play_score((const uint8_t *)&evade2_06_stage_3_boss);
    }
  }  
  else if (i == 6) {
    arduboy.print(sizeof(evade2_10_game_over));
    if (playingIndex != i) {
      playingIndex = i;
      atm_synth_play_score((const uint8_t *)&evade2_10_game_over);
    }
  }
  else {
    arduboy.print(" IDFK!!");
  }

  arduboy.print(" bytes ");
  arduboy.setCursor(0, 20);
  arduboy.print("i == "); arduboy.print(i);
  
  arduboy.display();
}
