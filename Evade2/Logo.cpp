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
  if (d->y < 5) {
    d->y++;
  }
  else if (!d->scrolled) {
    d->timer = 90;
    d->scrolled = TRUE;
  }
  if (d->scrolled) {
    Graphics::drawBitmap(d->x, d->y, modus_logo_img, 0x30, 0x36);
  }
  else {
    Graphics::drawBitmap(d->x, d->y, modus_logo_img, 0x30, 0x2b);
  }
  if (1) {
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
  d->x = 40;
  d->y = -40;
  d->timer = 48;
  d->scrolled = false;
  me->sleep(1, Logo::loop);
}
