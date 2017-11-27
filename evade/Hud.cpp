#include "Game.h"

#include "Hud.h"


byte life, power;

// PROTOTYPE HUD
// TODO: Connect with @mschwartz to leverage Object & Process to make drawing faster.

// TODO: Figureout how to track life (left) and weapon power (right).

// 13 == full. Anything less, and we draw "less meter"
void drawMeter(byte side, byte value) {

  //start at X:14
  // Draw 2 lines, skip one line, iterate 13 total times
  // if left, X:0, else X:128
  // Y Step is 3

  // TODO: Tighten up!
  // LEFT
  byte y = 15;
  if (side == 0) {
    // 13 total values
    for (byte i = 13; i > 0; i--) {
      if (value <= i) {
        arduboy.drawPixel(0, y, WHITE);
        arduboy.drawPixel(0, y+1, WHITE);
      } 
      else {
        arduboy.drawLine(0, y, 2, y, WHITE);
        arduboy.drawLine(0, y+1, 3, y+1, WHITE);
      }
      y += 3;
    }

  }
  else {
    for (byte i = 1; i < 13; i++) {
      if (i < value) {
        arduboy.drawPixel(127, y, WHITE);
        arduboy.drawPixel(127, y+1, WHITE);
      } 
      else {
        arduboy.drawLine(126, y, 128, y, WHITE);
        arduboy.drawLine(125, y+1, 128, y+1, WHITE);
      }
      y += 3;
    }
  }


}

void HUD::setLife(byte newLife) {
  life = newLife;
}

void HUD::setPower(byte newPower) {
  power = newPower;
}

void HUD::draw() {
  /* TOP LEFT Cockpit */
  arduboy.drawPixel(0,9,WHITE);
  arduboy.drawLine(1, 9, 7, 3, WHITE);
  arduboy.drawPixel(7, 0, WHITE);
  arduboy.drawPixel(7, 1, WHITE);
  arduboy.drawPixel(7, 2, WHITE);

  // arduboy.drawLine(7,0, 7, 3);

  /* TOP RIGHT Cockpit edge */
  arduboy.drawPixel(127, 9, WHITE);
  arduboy.drawLine(120, 3, 126, 9, WHITE);
  arduboy.drawPixel(120, 0, WHITE);
  arduboy.drawPixel(120, 1, WHITE);
  arduboy.drawPixel(120, 2, WHITE);


  /* BOTTOM LEFT Radar */
  arduboy.drawBitmap(0, 56, hud_bottom_left_radar, 8, 8, WHITE);


  /* BOTTOM RIGHT Radar */
  arduboy.drawBitmap(120, 56, hud_bottom_right_radar, 8, 8, WHITE);


  /* BOTTOM LEFT PEW */
  // TODO: Animate in and out when firing
  if (life > 5) {
    arduboy.drawBitmap(28, 56, hud_bottom_left_pew, 11, 8, WHITE);
  }

  /* BOTTOM RIGHT PEW */
  // TODO: Animate in and out when firing
  if (power > 5) {
    arduboy.drawBitmap(89, 56, hud_bottom_right_pew, 11, 8, WHITE);
  }
  
  drawMeter(0, life);
  drawMeter(1, power);


}
