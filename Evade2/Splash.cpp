#define DEBUGME
//#undef DEBUGME

#include "Evade2.h"
#include "img/modus_logo.h"



BOOL Splash::attract_mode = TRUE;

struct splash_data {
#ifdef ENABLE_ROTATING_TEXT
  FLOAT theta; // angle of rotating text
#endif
  WORD timer;
};
/**
  * Show Modus Create logo
  */

#ifdef SHOW_LOGO_SPLASH
void Splash::show_logo(Process *me) {
    register Object *o = me->o;
    Graphics::drawBitmap(40, 8, &modus_logo_img[2], 0x2a, 0x28);
    o->theta++;

    if (o->theta > 90) {
        o->theta = 0;
        me->sleep(1, Splash::wait);
        return;
    }

    me->sleep(1);
}
#endif

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
  d->timer--;
  if (d->timer < 0 || Controls::debounced(RIGHT_BUTTON)) {
    game_mode = MODE_ATTRACT;
    attract_mode = !attract_mode;
    ProcessManager::birth(Attract::entry);
    me->suicide();
    return;
  }
  if (d->timer & 16) {
    Font::scale = 0x100;
    Font::printf(45, 52, "START");
  }

  if (Controls::debounced(BUTTON_A) || Controls::debounced(BUTTON_B)) {
    ProcessManager::birth(Game::entry);
    me->suicide();
    return;
  }
  me->sleep(1);
}

void Splash::entry(Process *me, Object *o) {
  splash_data *d = (splash_data *)&o->x;
#ifdef ENABLE_ROTATING_TEXT
  d->theta = 90;
#endif
  d->timer = 240;

  Camera::vz = CAMERA_VZ;
  Sound::play_score(INTRO_SONG);
#ifdef SHOW_LOGO_SPLASH
  me->sleep(1, Splash::show_logo);
#else
    me->sleep(1, Splash::wait);
#endif
}
