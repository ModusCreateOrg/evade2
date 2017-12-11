#define DEBUGME
//#undef DEBUGME

#include "Evade2.h"

struct splash_data {
#ifdef ENABLE_ROTATING_TEXT
  FLOAT theta; // angle of rotating text
#endif
  BYTE settings; // higlight: FALSE = start game, TRUE = settings
  WORD timer;
};

// Splash process uses an Object that isn't displayed!
// The object structure provides some variable space we
// can use, saving precious global variable space.
void Splash::start_game(Process *me) {
  game_mode = MODE_GAME;
  Sound::stfu();
  Sound::play_score(STAGE_1_SONG);
  Player::init();
  ProcessManager::birth(Enemy::entry);
  ProcessManager::birth(Enemy::entry);
  ProcessManager::birth(Enemy::entry);
  //  ProcessManager::birth(Enemy_Scout::enemy_scout_process);
  //  ProcessManager::birth(Enemy_Heavy_Bomber::enemy_heavy_bomber_process);
  me->suicide();
}

/**
 * Display "Get Ready" for o->state frames
 */
void Splash::get_ready(Process *me, Object *o) {
  splash_data *d = (splash_data *)&o->x;

#ifdef ENABLE_ROTATING_TEXT
  Font::print_string_rotatedx(30, 35, d->theta, F("GET READY!"));
  d->theta += 12;
#else
  Font::printf(30, 35, "GET READY!");
#endif
  BYTE timer = d->timer;

  if (timer <= 1) {
    Splash::start_game(me);
    return;
  }
  d->timer--;
  me->sleep(1);
}

/**
 * Wait for the human to press the A button
 */
void Splash::wait(Process *me, Object *o) {
  splash_data *d = (splash_data *)&o->x;

  Font::scale = 0x200;
#ifdef ENABLE_ROTATING_TEXT
  Font::print_string_rotatedx(15, 25, d->theta, F("EVADE 2"));
  d->theta += 10;
  if (d->theta > 90 + 360 * 2) {
    d->theta = 90 + 360 * 2;
  }
#else
  Font::printf(15, 25, "EVADE 2");
#endif
  Font::scale = 0x100;
  d->timer++;
  if (d->timer & 16) {
    Font::scale = 0x100;
    const BYTE x = 32;
    Font::printf(x+4, 48, "PRESS A");
    Font::printf(x, 60, "TO START");
  }

  if (Controls::debounced(BUTTON_A)) {
    d->timer = 60; // how long to show "Get Ready"
#ifdef ENABLE_ROTATING_TEXT
    d->theta = 90;
#endif
    Sound::play_score(GET_READY_SONG);
    me->sleep(1, Splash::get_ready);
    return;
  }
  me->sleep(1);
}

void Splash::entry(Process *me, Object *o) {
  o = ObjectManager::alloc();
  me->o = o;
  o->lines = NULL;
  splash_data *d = (splash_data *)&o->x;
#ifdef ENABLE_ROTATING_TEXT
  d->theta = 90;
#endif
  d->timer = 0;
  d->settings = FALSE;

  Camera::vz = CAMERA_VZ;
  Sound::play_score(INTRO_SONG);
  me->sleep(1, Splash::wait);
}
