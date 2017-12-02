#ifndef ENEMY_SCOUT_IMG_H
#define ENEMY_SCOUT_IMG_H

#include "../Types.h"

// SVG Graphic source: svg_docs/scout_plain-1.svg
// Number bytes 67
const PROGMEM BYTE enemy_scout_img[] = {
    128,    // Width (128 px)
    64,    // Height (64 px)
    16,    // Number of rows of coords (16)
//  x0,     y0,    x1,    y1
    3,    -30,    13,    -14,
    13,    -14,    1,    18,
    1,    18,    3,    -30,
    -3,    -30,    -13,    -14,
    -13,    -14,    -1,    18,
    -1,    18,    -3,    -30,
    -8,    -22,    -18,    -32,
    -18,    -32,    -64,    -7,
    -64,    -7,    -23,    -18,
    -23,    -18,    -9,    32,
    -9,    32,    -5,    7,
    8,    -22,    18,    -32,
    18,    -32,    64,    -7,
    64,    -7,    23,    -18,
    23,    -18,    9,    32,
    9,    32,    5,    7
};

#endif
