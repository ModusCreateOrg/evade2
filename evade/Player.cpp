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

// PROTOTYPE HUD
// TODO: Connect with @mschwartz to leverage Object & Process to make drawing faster.

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

void Player::render_score() {
  char out[9];

  bcd_string(score, out);
  Font::print_string(4, 6, &out[3]);
}

void Player::after_render() {
  arduboy.invert(flags & PLAYER_FLAG_HIT);
  flags &= ~PLAYER_FLAG_HIT;



  Graphics::drawBitmap(43 , 56, hud_console_img, 0x2a, 0x08);


  drawMeter(0, life);
  drawMeter(1, power);
}
