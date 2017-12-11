#ifndef SOUND_H
#define SOUND_H

#include "Types.h"

const BYTE SFX_PLAYER_SHOOT = 1;
const BYTE SFX_ENEMY_SHOOT = 2;
const BYTE SFX_PLAYER_HIT_BY_ENEMY = 3;

// SONGS
const BYTE INTRO_SONG = 0;
const BYTE STAGE_1_SONG = 1;
const BYTE STAGE_1_BOSS_SONG = 2;
const BYTE STAGE_2_SONG = 3;
const BYTE STAGE_2_BOSS_SONG = 4;

const BYTE STAGE_3_BOSS_SONG = 7;
const BYTE GAME_OVER_SONG = 10;
const BYTE GET_READY_SONG = 11;

class Sound {
public:
  static void init();
  // TODO: getSize() a temp function that is only meant to be
  //       used for development to allow us to determine the size
  //       of a particular score and will be removed before launch.
  static long getSize();
  static void play_sound(BYTE id);
  static void stfu();
  static void play_score(BYTE id);
};
#endif
