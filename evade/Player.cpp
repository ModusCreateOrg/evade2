#define DEBUGME
//#undef DEBUGME

#include "Game.h"

#include "img/hud_console_img.h"

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
    Bullet::fire();
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
static void drawMeter(BYTE side, BYTE value, BYTE deltaX, BYTE deltaY) {

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
        Graphics::drawPixel(1 + deltaX, y + deltaY);
        Graphics::drawPixel(1 + deltaX, y + 1 + deltaY);
      }
      else {
        Graphics::drawLine(1 + deltaX, y + deltaY, 3 + deltaX, y + deltaY);
        Graphics::drawLine(1 + deltaX, y + 1 + deltaY, 4 + deltaX, y + 1 + deltaY);
      }
      y -= 3;
    }
  }
  else { // RIGHT
    for (BYTE i = 0; i < 10; i++) {
      if (i >= value) {
        Graphics::drawPixel(126 + deltaX, y + deltaY);
        Graphics::drawPixel(126 + deltaX, y + 1 + deltaY);
      }
      else {
        Graphics::drawLine(124 + deltaX, y + deltaY, 126 + deltaX, y + deltaY);
        Graphics::drawLine(123 + deltaX, y + 1 + deltaY, 126 + deltaX, y + 1 + deltaY);
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
  BYTE consoleX = 46,
       consoleY = 50,
       deltaX   = 0,
       deltaY   = 0;

  if (Controls::pressed(JOYSTICK_RIGHT)) {
    consoleX = 44;
    deltaX = -1;
  }
  else if (Controls::pressed(JOYSTICK_LEFT)) {
    consoleX = 48;
    deltaX = 1;
  }

  if (Controls::pressed(JOYSTICK_UP)) {
    consoleY = 48;
    deltaY = -1;
  }
  else if (Controls::pressed(JOYSTICK_DOWN)) {
    consoleY = 52;
    deltaY = 1;
  }  

  Graphics::drawBitmap(consoleX , consoleY, hud_console_img, 40, 16);

  drawMeter(0, life, deltaX, deltaY);
  drawMeter(1, power, deltaX, deltaY);

#else
  // Graphics::drawBitmap(107, 0, hud_top_right_img, 0x15, 0x0b);
  // Graphics::drawBitmap(116, 54, hud_bottom_right_img, 0x0b, 0x0b);
  Graphics::drawBitmap(43 , 56, hud_console_img, 40, 16);

  drawMeter(0, life);
  drawMeter(1, power);
#endif  


}
