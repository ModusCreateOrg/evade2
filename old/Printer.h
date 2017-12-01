#ifndef PRINTER_H
#define PRINTER_H

#include "Types.h"

class Printer : public Print {
public:
  Printer();

  void setCursor(WORD x, WORD y);
  void setTextSize(UBYTE s);
  size_t write(uint8_t c);
  void drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size);

protected:
  uint8_t cursor_x;
  uint8_t cursor_y;
  uint8_t textColor;
  uint8_t textBackground;
  uint8_t textSize;
  bool textWrap;
};

#endif
