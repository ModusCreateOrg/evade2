#ifndef EBULLET_IMG_H
#define EBULLET_IMG_H

#include "../Types.h"

const PROGMEM BYTE ebullet_img[] = {
  16, // width
  32, // height
  4,  // num rows
  0 - 8, 15 - 16, 7 - 8, 0 - 16,
  7 - 8, 0 - 16, 15 - 8, 15 - 16,
  15 - 8, 15 - 16, 7 - 8, 31 - 16,
  7 - 8, 31 - 16, 0 - 8, 15 - 16,
};

#endif
