#ifndef ENEMY_HEAVY_BOMBER_IMG_H
#define ENEMY_HEAVY_BOMBER_IMG_H

#include "../Types.h"
// SVG Graphic source: svg_docs/enemy2-lines.svg
// Number bytes 55
const PROGMEM BYTE enemy_heavy_bomber_img[] = {
    64, // Width (64 px)
    42, // Height (42 px)
    13, // Number of rows of coords (13)
//  x0,     y0,    x1,    y1
    -8,    12,    9,    12,
    -32,    -21,    -9,    4,
    -8,    4,    -18,    14,
    8,    4,    18,    13,
    -18,    13,    -9,    22,
    -9,    11,    -9,    21,
    9,    11,    9,    22,
    17,    13,    8,    22,
    -31,    -21,    -3,    -3,
    8,    4,    31,    -20,
    32,    -21,    3,    -3,
    -3,    -4,    4,    -4,
    -5,    1,    5,    1
};
#endif