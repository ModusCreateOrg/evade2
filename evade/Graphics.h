#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Game.h"

#define INLINE_PLOT
//#undef INLINE_PLOT

// SMART_ERASE is experimental and appears to be too slow for production use at this time
// We can speed it up by tracking the lines and points drawn and simply erasing those.
// The cost is precious SRAM.
#define SMART_ERASE
#undef SMART_ERASE

class Graphics {
public:
  static void drawPixel(WORD x, WORD y);
  static void drawLine(WORD x, WORD y, WORD x2, WORD y2);
  static void drawVectorGraphic(const BYTE *graphic, float x, float y, float theta, float scaleFactor);
  static void explodeVectorGraphic(const BYTE *graphic, float x, float y, float theta, float scaleFactor, BYTE step);
#ifdef SMART_ERASE
  static void eraseLine(WORD x, WORD y, WORD x2, WORD y2);
  static void eraseVectorGraphic(const uint8_t *graphic, float x, float y, float theta, float scaleFactor){
#endif
  };

#endif
