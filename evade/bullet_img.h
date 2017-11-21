#ifndef BULLET_IMG_H
#define BULLET_IMG_H

#include "Types.h"
// drawLine(x0, y0, x1, y1, color);

// GRAPHIC: enemy1.svg
// Number bytes 52
const PROGMEM UBYTE bullet1_img[] = {
  16, 2, 2,
  0, 0, 15, 15,
  0, 15, 15, 0,
  0, 0, 15, 0,
  15, 0, 15, 15,
  0, 15, 15, 15,
  0, 15, 0, 0,
};

const PROGMEM UBYTE bullet2_img[] = {
  16, 2, 2,
  8, 0, 8, 15,
  0, 8, 15, 8,
  0, 0, 15, 0,
  15, 0, 15, 15,
  0, 15, 15, 15,
  0, 15, 0, 0,
};
#endif
