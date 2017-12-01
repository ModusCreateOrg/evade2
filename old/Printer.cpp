#include "Game.h"
#include "Printer.h"
#include "glcdfont.c"

Printer::Printer() {
  cursor_x = 0;
  cursor_y = 0;
  textColor = 1;
  textBackground = 0;
  textSize = 1;
  textWrap = 0;
}

void Printer::setCursor(WORD x, WORD y) {
  cursor_x = x;
  cursor_y = y;
}

void Printer::setTextSize(UBYTE s) {
  textSize = max(1, s);
}

size_t Printer::write(uint8_t c) {
  if (c == '\n') {
    cursor_y += textSize * 8;
    cursor_x = 0;
  }
  else if (c == '\r') {
    // skip em
  }
  else {
    drawChar(cursor_x, cursor_y, c, textColor, textBackground, textSize);
    cursor_x += textSize * 6;
    if (textWrap && (cursor_x > (WIDTH - textSize * 6))) {
      // calling ourselves recursively for 'newline' is
      // 12 bytes smaller than doing the same math here
      write('\n');
    }
  }
  return 1;
}

void Printer::drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size) {
  uint8_t line;
  bool draw_background = bg != color;
  const unsigned char *bitmap = font + c * 5;

  if ((x >= WIDTH) ||             // Clip right
      (y >= HEIGHT) ||            // Clip bottom
      ((x + 5 * size - 1) < 0) || // Clip left
      ((y + 8 * size - 1) < 0)    // Clip top
      ) {
    return;
  }

  for (uint8_t i = 0; i < 6; i++) {
    line = pgm_read_byte(bitmap++);
    if (i == 5) {
      line = 0x0;
    }

    for (uint8_t j = 0; j < 8; j++) {
      uint8_t draw_color = (line & 0x1) ? color : bg;

      if (draw_color || draw_background) {
        for (uint8_t a = 0; a < size; a++) {
          for (uint8_t b = 0; b < size; b++) {
            Graphics::drawPixel(x + (i * size) + a, y + (j * size) + b, draw_color);
          }
        }
      }
      line >>= 1;
    }
  }
}
