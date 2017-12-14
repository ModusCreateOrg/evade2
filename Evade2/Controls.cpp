#define DEBUGME

#include "Evade2.h"

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

BOOL Controls::debounced(UBYTE key) {
  BOOL v = dkeys & key;
  dkeys &= ~key;
  return v;
}

BOOL Controls::pressed(UBYTE key) {
  return ckeys & key;
}
