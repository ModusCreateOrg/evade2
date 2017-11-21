#include "Game.h"
#include "Object.h"

#define DEBUGME

void Object::move() {
  x += vx;
  y += vy;
  z += vz;
}

void drawVectorGraphic(const uint8_t *graphic, float x, float y, float theta, float scaleFactor) {

  // Can't do anything here.
  if (scaleFactor == 0) {
    return;
  }

  byte width = pgm_read_byte(graphic),
       height = pgm_read_byte(++graphic);

  float imgCtrWidth = (width / scaleFactor) / 2,
        imgCtrHeight = (height / scaleFactor ) / 2;


  byte numRows = pgm_read_byte(++graphic);

  float rad = float(theta) * 3.1415926 / 180,
        sint = sin(rad),
        cost = cos(rad);

  for (byte i = 0; i < numRows; i++) {


    float x0 = (pgm_read_byte(++graphic) / scaleFactor + x) - imgCtrWidth,
          y0 = (pgm_read_byte(++graphic) / scaleFactor + y) - imgCtrHeight,
          x1 = (pgm_read_byte(++graphic) / scaleFactor + x) - imgCtrWidth,
          y1 = (pgm_read_byte(++graphic) / scaleFactor + y) - imgCtrHeight;

    arduboy.drawLine(
        (x0 - x) * cost - (y0 - y) * sint + x,
        (y0 - y) * cost + (x0 - x) * sint + y,
        (x1 - x) * cost - (y1 - y) * sint + x,
        (y1 - y) * cost + (x1 - x) * sint + y,
        WHITE
      );
  }
}

void Object::draw() {
  float zz = (z - Camera::z) * 2;
  float ratio = 128 / (zz + 128);

  register float cx = (Camera::x - x) * ratio + SCREEN_WIDTH / 2;
  register float cy = (Camera::y - y) * ratio + SCREEN_HEIGHT / 2;

  drawVectorGraphic(lines, cx, cy, float(theta), 1 / ratio);
}
