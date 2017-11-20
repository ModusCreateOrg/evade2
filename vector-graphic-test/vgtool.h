#ifndef VGTOOL_H
#define VGTOOL_H

// drawLine(x0, y0, x1, y1, color);



// GRAPHIC: fighter1.svg
// Number bytes 52
const PROGMEM uint8_t fighter1[] = {
    0x0D, // Number of rows of coords
    0x00,   0x00,   0x80,   0x00,       // x1:0, y1:0, x2:0, y2:0,
    0x00,   0x80,   0x80,   0x80,       // x1:0, y1:128, x2:0, y2:128,
    0x00,   0x00,   0x00,   0x80,       // x1:0, y1:0, x2:0, y2:128,
    0x80,   0x00,   0x80,   0x80,       // x1:128, y1:0, x2:128, y2:128,
    0x00,   0x00,   0x2e,   0x2e,       // x1:0, y1:0, x2:0, y2:46,
    0x52,   0x52,   0x80,   0x80,       // x1:82, y1:82, x2:82, y2:128,
    0x01,   0x80,   0x2e,   0x53,       // x1:1, y1:128, x2:1, y2:83,
    0x80,   0x00,   0x51,   0x2e,       // x1:128, y1:0, x2:128, y2:46,
    0x3f,   0x36,   0x3f,   0x0f,       // x1:63, y1:54, x2:63, y2:15,
    0x00,   0x00,   0x2e,   0x2e,       // x1:0, y1:0, x2:0, y2:46,
    0x3f,   0x72,   0x3f,   0x4b,       // x1:63, y1:114, x2:63, y2:75,
    0x0f,   0x41,   0x36,   0x41,       // x1:15, y1:65, x2:15, y2:65,
    0x48,   0x41,   0x6f,   0x41        // x1:72, y1:65, x2:72, y2:65
};



#endif
