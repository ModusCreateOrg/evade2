#include "Game.h"
#include "Object.h"

void Object::move() {
  x += vx;
  y += vy;
  z += vz;
}

void drawVectorGraphic(const UBYTE *graphic, FIXED x, FIXED y, FIXED scaleFactor) {
  // unsigned short graphicSize = sizeof(graphic);
  // Can't do anything here.
  if (scaleFactor == 0) {
    return;
  }

  UWORD width = fixed(pgm_read_byte(graphic) / 2);
  FIXED imgCtr = fdiv(width, scaleFactor);
  byte numRows = pgm_read_byte(++graphic);

  for (byte i = 0; i < numRows; i++) {
    // byte bite = ++graphic;
    // arduboy.print(bite);

    FIXED x0 = (fdiv(fixed(pgm_read_byte(++graphic)), scaleFactor) + x) - imgCtr,
          y0 = (fdiv(fixed(pgm_read_byte(++graphic)), scaleFactor) + y) - imgCtr,
          x1 = (fdiv(fixed(pgm_read_byte(++graphic)), scaleFactor) + x) - imgCtr,
          y1 = (fdiv(fixed(pgm_read_byte(++graphic)), scaleFactor) + y) - imgCtr;

    arduboy.drawLine(
        fint(x0),
        fint(y0),
        fint(x1),
        fint(y1),
        WHITE);
  }
}

void Object::draw() {
  // calculate width,height of viewing pyrmid at distance from camera in z
  //  register const UBYTE *graphic = lines;
  //  register BYTE num_lines = pgm_read_byte(graphic);

  FIXED center = fixed(128);
  FIXED zz = fmul((z - Camera::z), fixed(2));
  FIXED ratio = fdiv(center, (zz + center));
  FIXED imgCtr = (128 * ratio) / 2;

  FIXED cx = fmul(Camera::x - x, ratio) + fixed(SCREEN_WIDTH / 2);
  FIXED cy = fmul(Camera::y - y, ratio) + fixed(SCREEN_HEIGHT / 2);

  drawVectorGraphic(lines, fint(cx), fint(cy), fdiv(fixed(1), ratio));
}
