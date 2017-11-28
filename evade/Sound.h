#ifndef SOUND_H
#define SOUND_H

const int FIRE_SOUND = 1;

const int DEMO_SCORE = 1;

class Sound {
public:
  static void init();
// TODO: getSize() a temp function that is only meant to be  
//       used for development to allow us to determine the size  
//       of a particular score and will be removed before launch.
  static long getSize();
  static void play_sound(int id);
  static void play_score(int id);
};
#endif
