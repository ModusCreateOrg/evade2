#include "Evade2.h"

#include "img/modus_logo.h"

/**
  * Show Modus Create logo
  */

void Logo::loop(Process *me, Object *o) {
  if (o->y < 8) {
    o->y++;
  }
  else if (!o->state) {
    o->timer = 90;
    o->state = TRUE;
  }
  Graphics::drawBitmap(o->x, o->y, &modus_logo_img[2], 0x2a, 0x28);
  if (o->state) {
    Font::printf(8, 56, "Modus Create");
  }
  if (--o->timer < 0) {
    ProcessManager::birth(Splash::entry);
    me->suicide();
  }
  else {
    me->sleep(1);
  }
}

void Logo::entry(Process *me, Object *o) {
  game_mode = MODE_LOGO;
  o->x = 40;
  o->y = -40;
  o->timer = 48;
  me->sleep(1, Logo::loop);
}
