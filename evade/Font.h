#ifndef FONT_H
#define FONT_H

#include "Game.h"

// this doesn't seem right, but it will probably work
// as in, Font::fprint(fmt, args...)
#define fprint(x, y, fmt, ...) _fprint(x, y, F(fmt), ##__VA_ARGS__)

class Font {
public:
  // write returns width of character
  static BYTE write(BYTE x, BYTE y, char c);
  static void _fprint(BYTE x, BYTE y, const __FlashStringHelper *ifsh, ...);
};

#endif
