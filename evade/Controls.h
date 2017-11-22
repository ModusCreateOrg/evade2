#ifndef CONTROLS_H
#define CONTROLS_H

class Controls;

#include "Game.h"

#define JOYSTICK_UP (1 << 0)
#define JOYSTICK_DOWN (1 << 1)
#define JOYSTICK_LEFT (1 << 2)
#define JOYSTICK_RIGHT (1 << 3)
#define BUTTON_A (1 << 4)
#define BUTTON_B (1 << 5)

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
  static void run();
  static inline BOOL debounced(UBYTE key) {
    BOOL v = dkeys & key;
    dkeys &= ~key;
    return v;
  }
  static inline BOOL pressed(UBYTE key) {
    return ckeys & key;
  }
};

#endif
