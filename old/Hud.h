#ifndef HUD_H
#define HUD_H

#if 0
#include "Game.h"

/// hud_bottom_left_radar.png
// 8x8
PROGMEM const unsigned char hud_bottom_left_radar[] = {
  0xBD, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C
};

// hud_bottom_right_radar.png
// 8x8
PROGMEM const unsigned char hud_bottom_right_radar[] = {
  0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0xBD
};

// hud_bottom_right_pew.png
// 11x8
PROGMEM const unsigned char hud_bottom_right_pew[] = {
  0x01, 0x4A, 0x5C, 0xFE, 0xAC, 0x18, 0x8E, 0xD8, 0xB0, 0x40,
  0xA0
};

// hud_bottom_left_pew.png
// 11x8
PROGMEM const unsigned char hud_bottom_left_pew[] = {
  0xA0, 0x40, 0xB0, 0xD8, 0x8E, 0x18, 0xAC, 0xFE, 0x5C, 0x4A,
  0x01
};

class HUD {
public:
  static void setPower(BYTE newPower);
  static void setLife(BYTE newLife);
  static void draw();
};
#endif

#endif
