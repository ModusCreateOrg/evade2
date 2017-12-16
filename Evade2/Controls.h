#ifndef CONTROLS_H
#define CONTROLS_H

class Controls;

#include "Evade2.h"

#define JOYSTICK_UP UP_BUTTON
#define JOYSTICK_DOWN DOWN_BUTTON
#define JOYSTICK_LEFT LEFT_BUTTON
#define JOYSTICK_RIGHT RIGHT_BUTTON
#define BUTTON_A A_BUTTON
#define BUTTON_B B_BUTTON
#define JOYSTICK_ANY (JOYSTICK_UP | JOYSTICK_DOWN | JOYSTICK_LEFT | JOYSTICK_RIGHT)
#define BUTTON_ANY (BUTTON_A | BUTTON_B)

/**
 * Controls
 *
 * run() is called once per game loop to read the keys.
 *
 * ckeys = currrent keys
 * dkeys = debounced keys
 * rkeys = TRUE keys
 *
 * If journal is playing back, ckeys and dkeys will be the values in the
 * journal.  If you are
 * truly interested in the true buttons, use rkeys.
 *
 * ckeys bits are true if the button is currently down.
 * dkeys bits are latched.  They get set true if the button is down and stay latched even if
 * the button is released.  The code must reset the bits to detect the next button down.
 * You can use the debounced() method to test and reset button bit(s).
 */
class Controls {
public:
  static UBYTE ckeys, dkeys, rkeys;

public:
  static void reset();
  static void run();
  static BOOL debounced(UBYTE key);
  static BOOL pressed(UBYTE key);
};

#endif
