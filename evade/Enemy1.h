#ifndef ENEMY1_H
#define ENEMY1_H

#include "Process.h"
#include "Types.h"

/**
 * enemy1 process.
 *
 * We only expose the initial state/function as extern here, so it can be ProcessManager::birth()
 * from anywhere.
 *
 * The remaining states are static/local to the enemy1.cpp file.
 */
extern void enemy1_process(Process *me);


// SVG Graphic source: svg_docs/enemy1-edited-with-AI.svg
// Number bytes 187
const PROGMEM uint8_t enemy1[] = {
    0x80,   // Width (128 px)
    0x40,   // Height (64 px)
    0x2E,   // Number of rows of coords (46)
    0x00,   0x19,   0x2E,   0x00,       // x1:0, y1:25, x2:46, y2:0,
    0x00,   0x1A,   0x00,   0x19,       // x1:0, y1:26, x2:0, y2:25,
    0x29,   0x0E,   0x00,   0x1A,       // x1:41, y1:14, x2:0, y2:26,
    0x37,   0x40,   0x29,   0x0E,       // x1:55, y1:64, x2:41, y2:14,
    0x37,   0x40,   0x37,   0x40,       // x1:55, y1:64, x2:55, y2:64,
    0x37,   0x40,   0x37,   0x40,       // x1:55, y1:64, x2:55, y2:64,
    0x3A,   0x27,   0x37,   0x40,       // x1:58, y1:39, x2:55, y2:64,
    0x3F,   0x32,   0x3A,   0x27,       // x1:63, y1:50, x2:58, y2:39,
    0x3F,   0x32,   0x3F,   0x32,       // x1:63, y1:50, x2:63, y2:50,
    0x3C,   0x03,   0x3F,   0x32,       // x1:60, y1:3, x2:63, y2:50,
    0x41,   0x32,   0x44,   0x03,       // x1:65, y1:50, x2:68, y2:3,
    0x41,   0x32,   0x41,   0x32,       // x1:65, y1:50, x2:65, y2:50,
    0x46,   0x27,   0x41,   0x32,       // x1:70, y1:39, x2:65, y2:50,
    0x49,   0x40,   0x46,   0x27,       // x1:73, y1:64, x2:70, y2:39,
    0x49,   0x40,   0x49,   0x40,       // x1:73, y1:64, x2:73, y2:64,
    0x49,   0x40,   0x49,   0x40,       // x1:73, y1:64, x2:73, y2:64,
    0x57,   0x0E,   0x49,   0x40,       // x1:87, y1:14, x2:73, y2:64,
    0x80,   0x1A,   0x57,   0x0E,       // x1:128, y1:26, x2:87, y2:14,
    0x80,   0x19,   0x80,   0x1A,       // x1:128, y1:25, x2:128, y2:26,
    0x52,   0x00,   0x80,   0x19,       // x1:82, y1:0, x2:128, y2:25,
    0x47,   0x07,   0x52,   0x00,       // x1:71, y1:7, x2:82, y2:0,
    0x45,   0x03,   0x47,   0x07,       // x1:69, y1:3, x2:71, y2:7,
    0x39,   0x07,   0x3B,   0x03,       // x1:57, y1:7, x2:59, y2:3,
    0x49,   0x3F,   0x52,   0x01,       // x1:73, y1:63, x2:82, y2:1,
    0x46,   0x27,   0x49,   0x3F,       // x1:70, y1:39, x2:73, y2:63,
    0x4E,   0x13,   0x46,   0x27,       // x1:78, y1:19, x2:70, y2:39,
    0x4E,   0x13,   0x4E,   0x13,       // x1:78, y1:19, x2:78, y2:19,
    0x4E,   0x13,   0x4E,   0x13,       // x1:78, y1:19, x2:78, y2:19,
    0x47,   0x07,   0x4E,   0x13,       // x1:71, y1:7, x2:78, y2:19,
    0x47,   0x07,   0x47,   0x07,       // x1:71, y1:7, x2:71, y2:7,
    0x39,   0x07,   0x2E,   0x01,       // x1:57, y1:7, x2:46, y2:1,
    0x32,   0x13,   0x39,   0x07,       // x1:50, y1:19, x2:57, y2:7,
    0x3A,   0x27,   0x32,   0x13,       // x1:58, y1:39, x2:50, y2:19,
    0x37,   0x3F,   0x3A,   0x27,       // x1:55, y1:63, x2:58, y2:39,
    0x29,   0x0E,   0x2E,   0x01,       // x1:41, y1:14, x2:46, y2:1,
    0x01,   0x19,   0x29,   0x0E,       // x1:1, y1:25, x2:41, y2:14,
    0x7F,   0x19,   0x52,   0x01,       // x1:127, y1:25, x2:82, y2:1,
    0x57,   0x0E,   0x7F,   0x19,       // x1:87, y1:14, x2:127, y2:25,
    0x57,   0x0E,   0x52,   0x01,       // x1:87, y1:14, x2:82, y2:1,
    0x4A,   0x3E,   0x57,   0x0E,       // x1:74, y1:62, x2:87, y2:14,
    0x37,   0x3E,   0x2E,   0x01,       // x1:55, y1:62, x2:46, y2:1,
    0x29,   0x0E,   0x37,   0x3E,       // x1:41, y1:14, x2:55, y2:62,
    0x3F,   0x32,   0x3B,   0x03,       // x1:63, y1:50, x2:59, y2:3,
    0x32,   0x13,   0x3F,   0x32,       // x1:50, y1:19, x2:63, y2:50,
    0x4E,   0x13,   0x45,   0x03,       // x1:78, y1:19, x2:69, y2:3,
    0x41,   0x32,   0x4E,   0x13,       // x1:65, y1:50, x2:78, y2:19,

};



#endif
