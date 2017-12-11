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

static UBYTE swap_keys(UBYTE key) {
  // if (app_settings & SETTINGS_SWAP_CONTROLS) {
  //   UBYTE new_key = 0;
  //   if (key & BUTTON_A) {
  //     new_key |= BUTTON_B;
  //   }
  //   if (key & BUTTON_B) {
  //     new_key |= BUTTON_A;
  //   }
  //   if (key & JOYSTICK_UP) {
  //     new_key |= JOYSTICK_DOWN;
  //   }
  //   if (key & JOYSTICK_DOWN) {
  //     new_key |= JOYSTICK_UP;
  //   }
  //   if (key & JOYSTICK_LEFT) {
  //     new_key |= JOYSTICK_RIGHT;
  //   }
  //   if (key & JOYSTICK_RIGHT) {
  //     new_key |= JOYSTICK_LEFT;
  //   }
  //   return new_key;
  // }
  // else {
    return key;
  // }
}

BOOL Controls::debounced(UBYTE key) {
  // key = swap_keys(key);
  BOOL v = dkeys & key;
  dkeys &= ~key;
  return v;
}

BOOL Controls::pressed(UBYTE key) {
  return ckeys & swap_keys(key);
}
