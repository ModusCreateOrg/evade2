#define DEBUGME
#include "Game.h"

UBYTE Controls::rkeys = 0;
UBYTE Controls::ckeys = 0;
UBYTE Controls::dkeys = 0;

void Controls::run() {
  UBYTE buttons = 0;

#ifdef POLL_HARDWARE_KEYS
// using ports here is ~100 bytes smaller than digitalRead()
#ifdef AB_DEVKIT
  // down, left, up
  buttons = ((~PINB) & B01110000);
  // right button
  buttons = buttons | (((~PINC) & B01000000) >> 4);
  // A and B
  buttons = buttons | (((~PINF) & B11000000) >> 6);
#elif defined(ARDUBOY_10)
  // down, up, left right
  buttons = ((~PINF) & B11110000);
  // A (left)
  buttons = buttons | (((~PINE) & B01000000) >> 3);
  // B (right)
  buttons = buttons | (((~PINB) & B00010000) >> 2);
#endif
#else
  arduboy.pollButtons();
  if (arduboy.pressed(UP_BUTTON)) {
    buttons |= JOYSTICK_UP;
  }
  if (arduboy.pressed(DOWN_BUTTON)) {
    buttons |= JOYSTICK_DOWN;
  }
  if (arduboy.pressed(LEFT_BUTTON)) {
    buttons |= JOYSTICK_LEFT;
  }
  if (arduboy.pressed(RIGHT_BUTTON)) {
    buttons |= JOYSTICK_RIGHT;
  }
  if (arduboy.pressed(A_BUTTON)) {
    buttons |= BUTTON_A;
  }
  if (arduboy.pressed(B_BUTTON)) {
    buttons |= BUTTON_B;
  }
#endif
  dkeys = buttons ^ ckeys & buttons;
  ckeys = buttons;
  rkeys = buttons;
}
