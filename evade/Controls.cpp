#define DEBUGME
#include "Game.h"

UBYTE Controls::rkeys = 0;
UBYTE Controls::ckeys = 0;
UBYTE Controls::dkeys = 0;

void Controls::reset() {
  rkeys = ckeys = dkeys = 0;
}

void Controls::run() {
  UBYTE buttons = arduboy.buttonsState();
  dkeys = (buttons ^ ckeys) & buttons;
  ckeys = buttons;
  rkeys = buttons;
}
