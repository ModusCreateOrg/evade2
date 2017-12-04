#ifndef EBULLET_IMG_H
#define EBULLET_IMG_H

#include "../Types.h"

const PROGMEM BYTE ebullet_img[] = {
  8, // width
  8, // height
  4, // num rows
  0 - 4, 0 - 4, 7 - 4, 0 - 4,
  7 - 4, 0 - 4, 7 - 4, 7 - 4,
  7 - 4, 7 - 4, 0 - 4, 7 - 4,
  0 - 4, 7 - 4, 0 - 4, 0 - 4,
  40, // theta
};

const PROGMEM BYTE emissile_img[] = {
  16, // width
  16, // height
  9, // num rows
   1 - 8,  1 - 8,  5 - 8,  5 - 8,
   5 - 8,  4 - 8, 12 - 8,  4 - 8,
  11 - 8,  5 - 8, 16 - 8,  0 - 8,
   4 - 8,  5 - 8,  4 - 8, 12 - 8,
  12 - 8,  5 - 8, 12 - 8, 12 - 8,
   5 - 8, 12 - 8, 12 - 8, 12 - 8,
   5 - 8, 11 - 8,  0 - 8, 16 - 8,
  11 - 8, 11 - 8, 16 - 8, 16 - 8,
   8 - 8,  8 - 8,  9 - 8,  9 - 8, // dot in the middle
   8, //theta
};


#endif
