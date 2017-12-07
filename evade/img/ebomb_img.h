#ifndef EBOMB_IMG_H
#define EBOMB_IMG_H

#include "../Types.h"


const PROGMEM BYTE ebomb_img[] = {
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
