#ifndef SOUND_H
#define SOUND_H


const BYTE FIRE_SOUND = 1;

// SONGS
const BYTE INTRO_SONG = 1;
const BYTE STAGE_1_SONG = 2;
const BYTE STAGE_2_SONG = 3;

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
