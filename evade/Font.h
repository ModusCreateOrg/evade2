#ifndef FONT_H
#define FONT_H

#include "Game.h"

// this doesn't seem right, but it will probably work
// as in, Font::fprint(fmt, args...)
#define printf(x, y, fmt, ...) _printf(x, y, F(fmt), ##__VA_ARGS__)

class Font {
private:
  //static WORD scale; // 8.8 fixed point
  static FLOAT fscale;

public:
  // these routine return the width of whatever is printed to the screen
  static void setScale(WORD scale);
  static BYTE write(BYTE x, BYTE y, char c);
  static BYTE _printf(BYTE x, BYTE y, const __FlashStringHelper *ifsh, ...);
#ifdef ENABLE_ROTATING_TEXT
  static BYTE print_string_rotatedx(BYTE x, BYTE y, FLOAT angle, const __FlashStringHelper *ifsh);
#endif
  static BYTE print_string(BYTE x, BYTE y, char *s);
  static BYTE print_long(BYTE x, BYTE y, LONG n, BYTE base = 10);
  static BYTE print_float(BYTE x, BYTE y, double number, BYTE digits = 2);
};

#endif
