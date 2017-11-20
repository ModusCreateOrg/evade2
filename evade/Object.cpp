#include "Game.h"
#include "Object.h"

void Object::move() {
  x += vx;
  y += vy;
  z += vz;
}

void drawVectorGraphic(const uint8_t *graphic, float x, float y, float width, float scaleFactor) {
  // unsigned short graphicSize = sizeof(graphic);
  // Can't do anything here.
  if (scaleFactor == 0) {
    return;
  }

  float imgCtr = (width / scaleFactor) / 2;
  byte numRows = pgm_read_byte(graphic);

  for (byte i = 0; i < numRows; i++) {
    // byte bite = ++graphic;
    // arduboy.print(bite);

    float x0 = (pgm_read_byte(++graphic) / scaleFactor + x) - imgCtr,
          y0 = (pgm_read_byte(++graphic) / scaleFactor + y) - imgCtr,
          x1 = (pgm_read_byte(++graphic) / scaleFactor + x) - imgCtr,
          y1 = (pgm_read_byte(++graphic) / scaleFactor + y) - imgCtr;

    arduboy.drawLine(
        x0,
        y0,
        x1,
        y1,
        WHITE);
  }
}

void Object::draw() {
  // calculate width,height of viewing pyrmid at distance from camera in z
  //  register const UBYTE *graphic = lines;
  //  register BYTE num_lines = pgm_read_byte(graphic);

  float zz = (z - Camera::z) * 2;
  float ratio = 128 / (zz + 128);
  float imgCtr = (128 * ratio) / 2;

  register float cx = (Camera::x - x) * ratio + SCREEN_WIDTH / 2;
  register float cy = (Camera::y - y) * ratio + SCREEN_HEIGHT / 2;

  drawVectorGraphic(lines, cx, cy, 128, 1 / ratio);
}
