#define DEBUGME
//#undef DEBUGME

#include "Evade2.h"

#include "img/hud_console_img.h"


//TODO: Put in own files
PROGMEM const unsigned char crosshair_left_4x8[] = {
// width, height4, 8,
0x81, 0x42, 0x24, 0x99
};

// crosshair_left.png
// 8x16
PROGMEM const unsigned char crosshair_left_8x16[] = {
// width, height 8, 16,
0x01, 0x02, 0x04, 0x08, 0x12, 0x24, 0x48, 0x80, 0x80, 0x40, 
0x20, 0x10, 0x48, 0x24, 0x12, 0x01
};

// crosshair_right.png
// 4x8
PROGMEM const unsigned char crosshair_right_4x8[] = {
// width, height 4, 8,
0x99, 0x24, 0x42, 0x81
};

// crosshair_right.png
// 8x16
PROGMEM const unsigned char crosshair_right_8x16[] = {
// width, height 8, 16,
0x80, 0x48, 0x24, 0x12, 0x08, 0x04, 0x02, 0x01, 0x01, 0x12, 
0x24, 0x48, 0x10, 0x20, 0x40, 0x80
};

#define MAX_POWER 100
#define MAX_LIFE 100

BYTE Player::life = -1,
     Player::power = -1,
     Player::num_bullets = 0;

UBYTE Player::flags = 0;

BCD Player::score = 0;

void Player::init() {
  Camera::vz = CAMERA_VZ;
  power = MAX_POWER;
  life = MAX_LIFE;
  score = 0;
  num_bullets = 0;
  flags = 0;
}

void Player::add_score(BCD amount) {
  score = bcd_add(score, amount);
}

void Player::hit(BYTE amount) {
  life -= amount;
  if (life <= 0) {
    ProcessManager::birth(GameOver::entry);
  }
  else {
    Player::flags |= PLAYER_FLAG_HIT;
    Sound::play_sound(SFX_PLAYER_HIT_BY_ENEMY);
  }
}

void Player::before_render() {
  if (Controls::debounced(BUTTON_A)) {
    BYTE deltaX = 0,
         deltaY = 0;

    deltaX = Controls::pressed(JOYSTICK_RIGHT) ?  -12 : deltaX;
    deltaX = Controls::pressed(JOYSTICK_LEFT) ? 12: deltaX;

    deltaY = Controls::pressed(JOYSTICK_UP) ? -11 : deltaY;
    deltaY = Controls::pressed(JOYSTICK_DOWN) ? 13 : deltaY;

    Bullet::fire(deltaX, deltaY);
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
}

/************************************************************************/
/** HUD */
/************************************************************************/



#ifdef ENABLE_HUD_MOVEMENTS

// 13 == full. Anything less, and we draw "less meter"
static void drawMeter(BYTE side, BYTE value, BYTE deltaXMeter, BYTE deltaYMeter) {

  //start at X:14
  // Draw 2 lines, skip one line, iterate 13 total times
  // if left, X:0, else X:128
  // Y Step is 3

  // TODO: Tighten up!
  BYTE y = 45;
  value /= 10;
  if (side == 0) { // LEFT
    for (BYTE i = 0; i < 10; i++) {
      if (i >= value) {
        Graphics::drawPixel(1 + deltaXMeter, y + deltaYMeter);
        Graphics::drawPixel(1 + deltaXMeter, y + 1 + deltaYMeter);
      }
      else {
        Graphics::drawLine(1 + deltaXMeter, y + deltaYMeter, 3 + deltaXMeter, y + deltaYMeter);
        Graphics::drawLine(1 + deltaXMeter, y + 1 + deltaYMeter, 4 + deltaXMeter, y + 1 + deltaYMeter);
      }
      y -= 3;
    }
  }
  else { // RIGHT
    for (BYTE i = 0; i < 10; i++) {
      if (i >= value) {
        Graphics::drawPixel(126 + deltaXMeter, y + deltaYMeter);
        Graphics::drawPixel(126 + deltaXMeter, y + 1 + deltaYMeter);
      }
      else {
        Graphics::drawLine(124 + deltaXMeter, y + deltaYMeter, 126 + deltaXMeter, y + deltaYMeter);
        Graphics::drawLine(123 + deltaXMeter, y + 1 + deltaYMeter, 126 + deltaXMeter, y + 1 + deltaYMeter);
      }
      y -= 3;
    }
  }
}

#else

// 13 == full. Anything less, and we draw "less meter"
static void drawMeter(BYTE side, BYTE value) {

  //start at X:14
  // Draw 2 lines, skip one line, iterate 13 total times
  // if left, X:0, else X:128
  // Y Step is 3

  // TODO: Tighten up!
  BYTE y = 45;
  value /= 10;
  if (side == 0) { // LEFT
    for (BYTE i = 0; i < 10; i++) {
      if (i >= value) {
        Graphics::drawPixel(0, y);
        Graphics::drawPixel(0, y + 1);
      }
      else {
        Graphics::drawLine(0, y, 2, y);
        Graphics::drawLine(0, y + 1, 3, y + 1);
      }
      y -= 3;
    }
  }
  else { // RIGHT
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

#endif // #if ENABLE_HUD_MOVEMENTS

void Player::render_score() {
  char out[9];

  bcd_string(score, out);
  Font::print_string(4, 6, &out[3]);
}

void Player::after_render() {
  arduboy.invert(flags & PLAYER_FLAG_HIT);
  flags &= ~PLAYER_FLAG_HIT;

#ifdef ENABLE_HUD_MOVEMENTS
  BYTE consoleX    = 40,
       consoleY    = 58,
       deltaXMeter = 0,
       deltaYMeter = 0,
       deltaXCrossHairs = 0,
       deltaYCrossHairs = 0;

  if (Controls::pressed(JOYSTICK_RIGHT)) {
    consoleX = 38;
    deltaXMeter = -1;
    deltaXCrossHairs = 4;
  }
  else if (Controls::pressed(JOYSTICK_LEFT)) {
    consoleX = 42;
    deltaXMeter = 1;
    deltaXCrossHairs = -4;
  }

  if (Controls::pressed(JOYSTICK_UP)) {
    consoleY = 56;
    deltaYMeter = -1;
    deltaYCrossHairs = 4;
  }
  else if (Controls::pressed(JOYSTICK_DOWN)) {
    consoleY = 60;
    deltaYMeter = 1;
    deltaYCrossHairs = -4;
  }  

  Graphics::drawBitmap(consoleX , consoleY, &hud_console_img[2], hud_console_img[0], hud_console_img[1]);
  // Graphics::drawLine(64, 0, 64, 64);


  // Graphics::drawBitmap(50, 24, crosshair_left_4x8, 8, 16);
  // Graphics::drawBitmap(70, 24, crosshair_right_4x8, 8, 16);

  Graphics::drawBitmap(53 + deltaXCrossHairs, 30 + deltaYCrossHairs, crosshair_left_4x8, 4, 8);
  Graphics::drawBitmap(72 + deltaXCrossHairs, 30 + deltaYCrossHairs, crosshair_right_4x8, 4, 8);

  drawMeter(0, life, deltaXMeter, deltaYMeter);
  drawMeter(1, power, deltaXMeter, deltaYMeter);

#else
  // Graphics::drawBitmap(107, 0, hud_top_right_img, 0x15, 0x0b);
  // Graphics::drawBitmap(116, 54, hud_bottom_right_img, 0x0b, 0x0b);
  Graphics::drawBitmap(40, 58, &hud_console_img[2], hud_console_img[0], hud_console_img[1]);

  drawMeter(0, life);
  drawMeter(1, power);
#endif


}
