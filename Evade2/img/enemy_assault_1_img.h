
#ifndef ENEMY_ASSAULT_1_IMG_H
#define ENEMY_ASSAULT_1_IMG_H
// SVG Graphic source: svg_docs/output_from_ai/assault-1.svg
// Number bytes 59
const PROGMEM struct enemy_assault_1_img {
	uint8_t w;
	uint8_t h;
	uint8_t r;
	int8_t data[14*4];
} enemy_assault_1_img = {
	.w = 128,    // Width (128 px)
	.h = 54,    // Height (54 px)
	.r = 14,    // Number of rows of coords (14)
	.data = {
//  x0,     y0,    x1,    y1
    -21,    -27,    21,    16,
    -21,    16,    21,    -27,
    21,    -16,    11,    -5,
    11,    -5,    21,    5,
    -21,    5,    -11,    -5,
    -11,    -5,    -21,    -16,
    -11,    27,    -32,    5,
    -32,    5,    -21,    -5,
    11,    27,    32,    5,
    32,    5,    21,    -5,
    -21,    -16,    -64,    -16,
    21,    -16,    64,    -16,
    -11,    5,    0,    16,
    0,    16,    11,    5,
},
};
#endif

