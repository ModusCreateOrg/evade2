
#ifndef ENEMY_HEAVY_BOMBER_1_IMG_H
#define ENEMY_HEAVY_BOMBER_1_IMG_H
// SVG Graphic source: svg_docs/enemies_output_from_ai/heavy_bomber_1_img.svg
// Number bytes 35
const PROGMEM struct enemy_heavy_bomber_1_img {
    uint8_t w;
    uint8_t h;
    uint8_t r;
    int8_t data[8*4];
} enemy_heavy_bomber_1_img = {
    .w = 128,    // Width (128 px)
    .h = 55,    // Height (55 px)
    .r = 8,    // Number of rows of coords (8)
    .data = {
//  x0,     y0,    x1,    y1
    -64,    -18,    -18,    27,
    18,    27,    64,    -18,
    -46,    -18,    0,    27,
    0,    27,    46,    -18,
    -18,    0,    0,    -18,
    0,    -18,    18,    0,
    -64,    -18,    -55,    -27,
    64,    -18,    55,    -27,
},
};
#endif
