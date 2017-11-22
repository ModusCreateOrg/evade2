#ifndef SOUND_H
#define SOUND_H

const int FIRE_SOUND = 1;

const int DEMO_SCORE = 1;

class Sound {
public:
  static void init();
  static void play_sound(int id);
  static void play_score(int id);
};
#endif
