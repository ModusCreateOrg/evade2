#define DEBUGME
#undef DEBUGME

/**
 * Some of this code lifted from Arduino serial Print class and modified.
 * See: https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Print.cpp
 */

#include "Game.h"
#include "charset.h"

static const PROGMEM BYTE *const charset[] = {
  NULL, // space
  font_emark,
  font_dquote,
  NULL,        // #
  NULL,        // $
  NULL,        // %
  NULL,        // &
  font_squote, // '
  font_lt,     // (
  font_gt,     // )
  NULL,        // *
  font_plus,
  font_comma,
  font_minus,
  font_period,
  font_slash,
  font_0,
  font_1,
  font_2,
  font_3,
  font_4,
  font_5,
  font_6,
  font_7,
  font_8,
  font_9,
  font_colon,
  font_semicolon,
  font_lt, // <
  NULL,    // =
  font_gt, // >
  font_qmark,
  NULL, // @
  font_a,
  font_b,
  font_c,
  font_d,
  font_e,
  font_f,
  font_g,
  font_h,
  font_i,
  font_j,
  font_k,
  font_l,
  font_m,
  font_n,
  font_o,
  font_p,
  font_q,
  font_r,
  font_s,
  font_t,
  font_u,
  font_v,
  font_w,
  font_x,
  font_y,
  font_z,
  font_lt, // [
  NULL,    // '\'
  font_gt, // ]
  NULL,    // ^
  NULL,    // _
  NULL,    // ``
};

BYTE Font::scale = 1;

BYTE Font::write(BYTE x, BYTE y, char c) {
  PGM_P glyph;
  BYTE width = 6;

  glyph = (PGM_P)pgm_read_word(&charset[toupper(c) - 32]);
  if (glyph) {
    width = pgm_read_byte(glyph++);
    BYTE height = pgm_read_byte(glyph++),
         lines = pgm_read_byte(glyph++);

    for (BYTE i = 0; i < lines; i++) {
      BYTE x0 = pgm_read_byte(glyph++),
           y0 = pgm_read_byte(glyph++),
           x1 = pgm_read_byte(glyph++),
           y1 = pgm_read_byte(glyph++);
      Graphics::drawLine(x + x0 * scale, y + y0 * scale, x + x1 * scale, y + y1 * scale);
    }
  }
  return width * scale;
}

BYTE Font::print_string(BYTE x, BYTE y, char *s) {
  BYTE xx = x;
  char c;
  while (c = *s++) {
    BYTE width = Font::write(x, y, c);
    x += width;
  }
  return x - xx; // widdth of string printed
}

BYTE Font::print_long(BYTE x, BYTE y, LONG n, BYTE base) {
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2)
    base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (n);

  return print_string(x, y, str);
}

BYTE Font::print_float(BYTE x, BYTE y, double number, BYTE digits) {
  BYTE xx = x;
  if (isnan(number))
    return print_string(x, y, "nan");
  if (isinf(number))
    return print_string(x, y, "inf");
  if (number > 4294967040.0)
    return print_string(x, y, "ovf"); // constant determined empirically
  if (number < -4294967040.0)
    return print_string(x, y, "ovf"); // constant determined empirically

  // Handle negative numbers
  if (number < 0.0) {
    x += print_string(x, y, "-");
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i)
    rounding /= 10.0;

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  x += print_long(x, y, int_part, 10);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    x += print_string(x, y, ".");
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    x += print_long(x, y, toPrint, 10);
    remainder -= toPrint;
  }

  return x - xx;
}

BYTE Font::_printf(BYTE x, BYTE y, const __FlashStringHelper *ifsh, ...) {
  va_list ap;
  BYTE xx = x;
  char c;
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  va_start(ap, ifsh);

  while (c = pgm_read_byte(p++)) {
    if (c == '%') {
      c = pgm_read_byte(p++);
      switch (c) {
        case '\0':
          va_end(ap);
          return x - xx;
        case '%':
          x += Font::write(x, y, '%');
          break;
        case 'f':
          x += print_float(x, y, va_arg(ap, double));
          break;
        case 'd':
          x += print_long(x, y, (unsigned long)va_arg(ap, int));
          break;
        case 'x':
          x += print_long(x, y, (unsigned long)va_arg(ap, int) & 0xffff, 16);
          break;
        case 'l':
          x += print_long(x, y, va_arg(ap, long));
          break;
        default:
          x += Font::write(x, y, c);
          break;
      }
    }
    else {
      x += Font::write(x, y, c);
    }
  }
  va_end(ap);
  return xx - x;
}
