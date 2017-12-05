#include "Game.h"

#ifdef ENABLE_LED
void LED::rgb(BYTE r, BYTE g, BYTE b) {
  arduboy.setRGBled(r, g, b);
}

void LED::animate() {
  if (Player::flags & PLAYER_FLAG_HIT) {
    arduboy.setRGBled(0xff, 0xff, 0xff);
    return;
  }
  // RGB LED
  BYTE z = Camera::z / Camera::vz,
       r = 0,
       g = 0,
       b = 0;

  switch ((z >> 2) & 3) {
    case 0:
      //    case 7:
      r = LED_BRIGHTNESS;
      break;
    case 1:
    case 3:
      g = LED_BRIGHTNESS;
      break;
    case 2:
      //    case 4:
      b = LED_BRIGHTNESS;
      break;
  }
  arduboy.setRGBled(r, g, b);
}
#endif
