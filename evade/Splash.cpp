#define DEBUGME
#undef DEBUGME

#include "Game.h"
#include "img/logo_evade2.h"
#include "img/logo_modus_create.h"

// Splash process uses an Object that isn't displayed!
// The object structure provides some variable space we
// can use, saving precious global variable space.
void Splash::start_game(Process *me) {
  Sound::stfu();
  Sound::play_score(STAGE_1_SONG);
  game_mode = MODE_GAME;
  Player::init();
  ProcessManager::birth(Enemy_Scout::enemy_scout_process);
  ProcessManager::birth(Enemy_Heavy_Bomber::enemy_heavy_bomber_process);
  me->suicide();
}

/**
 * Display "Get Ready" for o->state frames
 */
void Splash::get_ready(Process *me) {
  Object *o = me->o;
  Font::print_string_rotatedx(30, 35, o->x, F("GET READY!"));
  o->x += 12;
  //  Font::printf(30, 35, "GET READY!");
  BYTE timer = o->state;

  if (timer <= 1) {
#ifdef ENABLE_LED
    LED::rgb(0, 0, 0);
#endif
    Splash::start_game(me);
    return;
  }
#ifdef ENABLE_LED
  else if (timer < 15) {
    LED::rgb(LED_BRIGHTNESS, 0, 0);
  }
  else if (timer < 30) {
    LED::rgb(0, LED_BRIGHTNESS, 0);
  }
  else {
    LED::rgb(0, 0, LED_BRIGHTNESS);
  }
#endif
  o->state--;
  me->sleep(1);
}

/**
 * Show Modus Create logo
 */
void Splash::show_logo(Process *me) {
    register Object *o = me->o;
    Graphics::drawBitmap(40, 8, &logo_modus_create[2], logo_modus_create[0], logo_modus_create[1], WHITE);
    o->theta++;

    if (o->theta > 90 || Controls::debounced(BUTTON_A)) {
        o->theta = 0;
        me->sleep(1, Splash::show_title);
        return;
    }

    me->sleep(1);
}

/**
 * Show Evade 2 logo
 */
void Splash::show_title(Process *me) {
    register Object *o = me->o;
    Graphics::drawBitmap(8, 10, &logo_evade2[2], logo_evade2[0], logo_evade2[1], WHITE);
    o->theta++;

    if (o->theta > 90 || Controls::debounced(BUTTON_A)) {
        o->theta = 0;
        me->sleep(1, Splash::wait);
        return;
    }

    me->sleep(1);
}

/**
 * Wait for the human to press the A button
 */
void Splash::wait(Process *me) {
  register Object *o = me->o;

  if (game_mode == MODE_SPLASH) {
    Font::scale = 2;
    Font::printf(15, 25, "EVADE 2");
    //    Font::print_string_rotatedx(15, 25, o->x, F("EVADE 2"));
    //    o->x += 10;
    Font::scale = 1;
    if (o->state & (1 << 4)) {
      Font::printf(40, 45, "Press A");
      Font::printf(35, 60, "to start");
#ifdef ENABLE_LED
      LED::rgb(0, LED_BRIGHTNESS, 0);
#endif
    }
#ifdef ENABLE_LED
    else {
      LED::rgb(0, 0, 0);
    }
#endif
  }
  else {
#ifdef ENABLE_LED
    LED::rgb(0, 0, 0);
#endif
    HighScore::renderHighScores();
  }
  if (Controls::debounced(BUTTON_A)) {
    o->state = 60; // how long to show "Get Ready"
    o->x = 0;
    me->sleep(1, Splash::get_ready);
    return;
  }
  o->state++;
  o->theta++;
  if (o->theta > 150) {
    o->theta = 0;
    if (game_mode == MODE_SPLASH) {
      game_mode = MODE_HIGHSCORES;
    }
    else {
      game_mode = MODE_SPLASH;
    }
  }
  me->sleep(1);
}

void Splash::splash_process(Process *me) {
  register Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = NULL;
  o->theta = 0;
  o->x = 0;

  Player::life = Player::power = -1;
  Camera::vz = CAMERA_VZ;
  Sound::play_score(INTRO_SONG);
  me->sleep(1, Splash::show_logo);
}
