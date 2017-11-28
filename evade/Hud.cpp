#include "Game.h"

static BYTE life = -1,
            power = -1;

// PROTOTYPE HUD
// TODO: Connect with @mschwartz to leverage Object & Process to make drawing faster.

// TODO: Figureout how to track life (left) and weapon power (right).

// 13 == full. Anything less, and we draw "less meter"
void drawMeter(BYTE side, BYTE value) {

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
    for (BYTE i = 1; i < 13; i++) {
      if (i < value) {
        Graphics::drawPixel(127, y);
        Graphics::drawPixel(127, y + 1);
      }
      else {
        Graphics::drawLine(126, y, 128, y);
        Graphics::drawLine(125, y + 1, 128, y + 1);
      }
      y += 3;
    }
  }
}

void HUD::setLife(BYTE newLife) {
  life = newLife;
}

void HUD::setPower(BYTE newPower) {
  power = newPower;
}

void HUD::draw() {
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
  Graphics::drawBitmap(28, 56, hud_bottom_left_pew, 11, 8);

  /* BOTTOM RIGHT PEW */
  // TODO: Animate in and out when firing
  Graphics::drawBitmap(89, 56, hud_bottom_right_pew, 11, 8);

  drawMeter(0, life);
  drawMeter(1, power);
}
