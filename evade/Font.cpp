#define DEBUGME
//#undef DEBUGME

#include "Game.h"
#include "fonts.h"

static const PROGMEM BYTE *const charset[] = {
  NULL, // space
  font_emark,
  font_quote,
  NULL,          // #
  NULL,          // $
  NULL,          // %
  NULL,          // &
  NULL,          // '
  font_lbracket, // (
  font_rbracket, // )
  NULL,          // *
  font_plus,
  font_comman,
  font_minus,
  font_dot,
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
  font_lbracket, // <
  NULL,          // =
  font_rbracket, // >
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
  font_lbracket, // [
  NULL,          // '\'
  font_rbracket, // ]
  NULL,          // ^
  NULL,          // _
  NULL,          // ``
};

BYTE Font::write(BYTE x, BYTE y, char c) {
  PGM_P glyph;
  BYTE width = 6;

  debug("c = %x\n", c);
  glyph = (PGM_P)pgm_read_word(&charset[c - 32]);
  debug("glyph = %x\n", glyph);
  if (glyph) {
    width = pgm_read_byte(glyph++);
    BYTE height = pgm_read_byte(glyph++),
         lines = pgm_read_byte(glyph++);

    debug("width, height, lines = %d,%d, %d\n", width, height, lines);
    for (BYTE i = 0; i < lines; i++) {
      BYTE x0 = pgm_read_byte(glyph++),
           y0 = pgm_read_byte(glyph++),
           x1 = pgm_read_byte(glyph++),
           y1 = pgm_read_byte(glyph++);
      debug("line % d : %d,%d,%d,%d\n", i, x0, y0, x1, y1);
      Graphics::drawLine(x + x0, y + y0, x + x1, y + y1);
    }
  }
  return width;
}

void Font::_fprint(BYTE x, BYTE y, const __FlashStringHelper *ifsh, ...) {
  va_list ap;
  char c;
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  va_start(ap, ifsh);

  while (c = pgm_read_byte(p++)) {
    BYTE width = Font::write(x, y, c);
    x += width + 2;
  }
}
