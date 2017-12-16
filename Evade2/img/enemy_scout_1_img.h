
#ifndef ENEMY_SCOUT_1_IMG_H
#define ENEMY_SCOUT_1_IMG_H
// SVG Graphic source: svg_docs/output_from_ai/assault_1_img.svg
// Number bytes 35
const PROGMEM struct enemy_scout_1_img {
    uint8_t w;
    uint8_t h;
    uint8_t r;
    int8_t data[8*4];
} enemy_scout_1_img = {
    .w = 128,    // Width (128 px)
    .h = 38,    // Height (38 px)
    .r = 8,    // Number of rows of coords (8)
    .data = {
//  x0,     y0,    x1,    y1
    9,    0,    27,    19,
    -27,    19,    -9,    0,
    -18,    -9,    -27,    0,
    -27,    0,    -9,    19,
    9,    19,    27,    0,
    27,    0,    18,    -9,
    -27,    19,    -64,    -19,
    27,    19,    64,    -19,
},
};
#endif

