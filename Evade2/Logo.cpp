#include "Evade2.h"

#include "img/modus_logo.h"

/**
  * Show Modus Create logo
  */

struct logo_data {
  BYTE x, y;
  WORD timer;
  BOOL scrolled;
};

void Logo::loop(Process *me, Object *o) {
  logo_data *d = (logo_data *)&o->x;
  if (d->y < 8) {
    d->y++;
  }
  else if (!d->scrolled) {
    d->timer = 90;
    d->scrolled = TRUE;
  }
  Graphics::drawBitmap(d->x, d->y, modus_logo_img, 0x2a, 0x28);
  if (d->scrolled) {
    Font::printf(48, 56, "Modus");
  }
  if (--d->timer < 0) {
    ProcessManager::birth(Splash::entry);
    me->suicide();
  }
  else {
    me->sleep(1);
  }
}

void Logo::entry(Process *me, Object *o) {
  logo_data *d = (logo_data *)&o->x;
  
  game_mode = MODE_LOGO;
  d->x = 43;
  d->y = -40;
  d->timer = 48;
  d->scrolled = false;
  me->sleep(1, Logo::loop);
}
