#define DEBUGME
//#undef DEBUGME

#include "Game.h"

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
  Sound::stfu();
  Sound::play_score(STAGE_1_SONG);
  game_mode = MODE_GAME;
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

void Splash::settings_screen(Process *me, Object *o) {
  splash_data *d = (splash_data *)&o->x;

  const BYTE x = 16, dy = 12;
  BYTE y = 6, carety = 0;

  Font::printf(x, 6, "SETTINGS");
  y += 16;
  Font::printf(x, y, "TOGGLE SOUND");
  if (d->settings == 0) {
    carety = y;
  }
  y += dy;
  Font::printf(x, y, "SWAP CONTROLS");
  if (d->settings == 1) {
    carety = y;
  }
  y += dy;
  Font::printf(x, y, "RESET SCORES");
  if (d->settings == 2) {
    carety = y;
  }
  y += dy;
  Font::printf(x, y, "RESET ALL");
  if (d->settings == 3) {
    carety = y;
  }
  Font::write(x - 14, carety, '>');
  if (Controls::debounced(JOYSTICK_LEFT | JOYSTICK_RIGHT)) {
#ifdef ENABLE_ROTATING_TEXT
    d->theta = 90;
#endif
    me->sleep(1, wait);
    return;
  }
  if (Controls::debounced(BUTTON_A)) {
    switch (d->settings) {
      case 0:
        app_settings ^= SETTINGS_AUDIO;
        HighScore::save_settings();
        break;
      case 1:
        app_settings ^= SETTINGS_SWAP_CONTROLS;
        HighScore::save_settings();
        break;
      case 2:
        HighScore::reset();
        break;
      case 3:
        HighScore::reset();
        app_settings = SETTINGS_AUDIO;
        HighScore::save_settings();
        break;
    }
  }
  if (Controls::debounced(JOYSTICK_UP)) {
    d->settings--;
    if (d->settings < 0) {
      d->settings = 3;
    }
  }
  if (Controls::debounced(JOYSTICK_DOWN)) {
    d->settings++;
    if (d->settings > 3) {
      d->settings = 0;
    }
  }
  me->sleep(1);
}

/**
 * Wait for the human to press the A button
 */
void Splash::wait(Process *me, Object *o) {
  splash_data *d = (splash_data *)&o->x;

  if (game_mode == MODE_SPLASH) {
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
    const BYTE x = 32;
    Font::printf(x, 45, "START GAME");
    Font::printf(x, 60, "SETTINGS");
    Font::write(x - 12, d->settings ? 60 : 45, '>');
    if (Controls::debounced(JOYSTICK_UP | JOYSTICK_DOWN)) {
      d->settings = !d->settings;
    }
  }
  else {
    HighScore::renderHighScores();
  }
  if (Controls::debounced(BUTTON_A)) {
    if (d->settings) {
      d->settings = 0;
      me->sleep(1, settings_screen);
      return;
    }
    d->timer = 60; // how long to show "Get Ready"
#ifdef ENABLE_ROTATING_TEXT
    d->theta = 90;
#endif
    Sound::play_score(GET_READY_SONG);
    me->sleep(1, Splash::get_ready);
    return;
  }
  d->timer++;
  debug("timer: %d\n", d->timer);
  if (d->timer > 150) {
    d->timer = 0;
    if (game_mode == MODE_SPLASH) {
      game_mode = MODE_HIGHSCORES;
    }
    else {
      game_mode = MODE_SPLASH;
    }
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

  Player::life = Player::power = -1;
  Camera::vz = CAMERA_VZ;
  Sound::play_score(INTRO_SONG);
  me->sleep(1, Splash::wait);
}
