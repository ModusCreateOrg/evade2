#define DEBUGME
//#undef DEBUGME

#include "Game.h"

#define MAX_POWER 100

BYTE Player::life = -1,
     Player::power = -1,
     Player::num_bullets = 0;

UBYTE Player::flags = 0;

BCD Player::score = 0;

void Player::init(Process *me) {
  Camera::vz = CAMERA_VZ;
  power = 100;
  life = 100;
  score = 0;
  num_bullets = 0;
  flags = 0;
}

void Player::loop(Process *me) {
  if (Controls::debounced(BUTTON_A)) {
    ProcessManager::birth(Bullet::bullet_process);
  }

  if (Controls::pressed(BUTTON_B)) {
    if (power > 0) {
      Camera::vz = CAMERA_VZ * 2;
      power--;
      if (power < 0) {
        power = 0;
      }
    }
    else {
      Camera::vz = CAMERA_VZ;
    }
  }
  else {
    Camera::vz = CAMERA_VZ;
    power++;
    if (power > MAX_POWER) {
      power = MAX_POWER;
    }
  }

  if (Controls::pressed(JOYSTICK_RIGHT)) {
    Camera::vx = -DELTACONTROL;
  }
  else if (Controls::pressed(JOYSTICK_LEFT)) {
    Camera::vx = DELTACONTROL;
  }
  else {
    Camera::vx = 0;
  }

  if (Controls::pressed(JOYSTICK_DOWN)) {
    Camera::vy = DELTACONTROL;
  }
  else if (Controls::pressed(JOYSTICK_UP)) {
    Camera::vy = -DELTACONTROL;
  }
  else {
    Camera::vy = 0;
  }

  me->sleep(1, Player::loop);
}

void Player::player_process(Process *me) {
  // initialize
  Player::init(me);
  me->sleep(1, Player::loop);
}

/************************************************************************/
/** HUD */
/************************************************************************/

// PROTOTYPE HUD
// TODO: Connect with @mschwartz to leverage Object & Process to make drawing faster.

// TODO: Figureout how to track life (left) and weapon power (right).

// 13 == full. Anything less, and we draw "less meter"
static void drawMeter(BYTE side, BYTE value) {

  //start at X:14
  // Draw 2 lines, skip one line, iterate 13 total times
  // if left, X:0, else X:128
  // Y Step is 3

  // TODO: Tighten up!
  // LEFT
  BYTE y = 15;
  if (side == 0) {
    // 13 total values
    for (BYTE i = 13; i > 0; i--) {
      if (value <= i) {
        Graphics::drawPixel(0, y);
        Graphics::drawPixel(0, y + 1);
      }
      else {
        Graphics::drawLine(0, y, 2, y);
        Graphics::drawLine(0, y + 1, 3, y + 1);
      }
      y += 3;
    }
  }
  else {
    value /= 10;
    y += 30;
    for (BYTE i = 0; i < 10; i++) {
      if (i >= value) {
        Graphics::drawPixel(127, y);
        Graphics::drawPixel(127, y + 1);
      }
      else {
        Graphics::drawLine(126, y, 128, y);
        Graphics::drawLine(125, y + 1, 128, y + 1);
      }
      y -= 3;
    }
  }
}

void Player::after_render() {
  arduboy.invert(flags & PLAYER_FLAG_HIT);
  flags &= ~PLAYER_FLAG_HIT;

  /// hud_bottom_left_radar.png
  // 8x8
  static PROGMEM const unsigned char hud_bottom_left_radar[] = {
    0xBD, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C
  };

  // hud_bottom_right_radar.png
  // 8x8
  static PROGMEM const unsigned char hud_bottom_right_radar[] = {
    0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0xBD
  };

  // hud_bottom_right_pew.png
  // 11x8
  //  static PROGMEM const unsigned char hud_bottom_right_pew[] = {
  //    0x01, 0x4A, 0x5C, 0xFE, 0xAC, 0x18, 0x8E, 0xD8, 0xB0, 0x40,
  //    0xA0
  //  };

  // hud_bottom_left_pew.png
  // 11x8
  //  static PROGMEM const unsigned char hud_bottom_left_pew[] = {
  //    0xA0, 0x40, 0xB0, 0xD8, 0x8E, 0x18, 0xAC, 0xFE, 0x5C, 0x4A,
  //    0x01
  //  };

  if (power < 0 && life < 0) {
    return;
  }

  /* TOP LEFT Cockpit */
  Graphics::drawPixel(0, 9);
  Graphics::drawLine(1, 9, 7, 3);
  Graphics::drawPixel(7, 0);
  Graphics::drawPixel(7, 1);
  Graphics::drawPixel(7, 2);

  // Graphics::drawLine(7,0, 7, 3);

  /* TOP RIGHT Cockpit edge */
  Graphics::drawPixel(127, 9);
  Graphics::drawLine(120, 3, 126, 9);
  Graphics::drawPixel(120, 0);
  Graphics::drawPixel(120, 1);
  Graphics::drawPixel(120, 2);

  /* BOTTOM LEFT Radar */
  Graphics::drawBitmap(0, 56, hud_bottom_left_radar, 8, 8);

  /* BOTTOM RIGHT Radar */
  Graphics::drawBitmap(120, 56, hud_bottom_right_radar, 8, 8);

  /* BOTTOM LEFT PEW */
  // TODO: Animate in and out when firing
  //  Graphics::drawBitmap(28, 56, hud_bottom_left_pew, 11, 8);

  /* BOTTOM RIGHT PEW */
  // TODO: Animate in and out when firing
  //  Graphics::drawBitmap(89, 56, hud_bottom_right_pew, 11, 8);

  drawMeter(0, life);
  drawMeter(1, power);

#ifdef ENABLE_LED_LOGIC
  // RGB LED
  BYTE z = Camera::z / Camera::vz,
       r = 0,
       g = 0,
       b = 0;

  switch ((z >> 3) & 7) {
    case 0:
    case 6:
      //    case 7:
      r = 0x3f;
      break;
    case 1:
    case 5:
      g = 0x3f;
      break;
    case 2:
    case 3:
      //    case 4:
      b = 0x3f;
      break;
    case 4:
      b = 0xff;
      break;
    case 7:
      r = 0xff;
      break;
  }
  arduboy.setRGBled(r, g, b);
#endif
}
