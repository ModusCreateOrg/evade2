#ifndef RADAR_BLIP_IMG_H
#define RADAR_BLIP_IMG_H

#include "../Types.h"

// Number bytes 11
const PROGMEM BYTE radar_blip_img[] = {
  // 2, // Width
  // 2, // height
  4, // num rows
  1 - 2, 0 - 2, 2 - 2, 0 - 2,
  0 - 2, 1 - 2, 3 - 2, 1 - 2,
  0 - 2, 2 - 2, 3 - 2, 2 - 2,
  1 - 2, 3 - 2, 2 - 2, 3 - 2,
};

#endif
