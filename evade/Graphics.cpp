/**
 * Portions of this class were lifted from the Arduboy2 library/class.
 * See https://github.com/MLXXXp/Arduboy2
 */

#define DEBUGME
#include "Game.h"

static UBYTE sBuffer[WIDTH * HEIGHT / 8];

static inline void swap(WORD &a, WORD &b) {
  WORD temp = a;
  a = b;
  b = temp;
}

void Graphics::display(BOOL clear) {
  arduboy.flipVertical(app_settings & SETTINGS_SWAP_CONTROLS);
  arduboy.flipHorizontal(app_settings & SETTINGS_SWAP_CONTROLS);
  arduboy.paintScreen(sBuffer, clear);
}

static const uint8_t bitshift_left[] PROGMEM = {
  _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7)
};

BOOL Graphics::drawPixel(WORD x, WORD y, UBYTE color) {
  if (x & ~0x7f || y & ~0x3f) {
    return FALSE;
  }

  WORD row_offset;
  WORD bit;

#if FALSE
  uint8_t row = (uint8_t)y / 8;
  row_offset = (row * WIDTH) + (uint8_t)x;
  bit = _BV((uint8_t)y % 8);
  if (color) {
    sBuffer[row_offset] |= bit;
  }
  else {
    sBuffer[row_offset] &= ~bit;
  }
#else
  // uint8_t row = (uint8_t)y / 8;
  // row_offset = (row*WIDTH) + (uint8_t)x;
  // bit = _BV((uint8_t)y % 8);

  // the above math can also be rewritten more simply as;
  //   row_offset = (y * WIDTH/8) & ~0b01111111 + (uint8_t)x;
  // which is what the below assembler does

  // local variable for the bitshift_left array pointer,
  // which can be declared a read-write operand
  volatile const UBYTE *bsl = bitshift_left;

  asm volatile(
      "mul %[width_offset], %A[y]\n"
      "movw %[row_offset], r0\n"
      "andi %A[row_offset], 0x80\n" // row_offset &= (~0b01111111);
      "clr __zero_reg__\n"
      "add %A[row_offset], %[x]\n"
      // mask for only 0-7
      "andi %A[y], 0x07\n"
      // Z += y
      "add r30, %A[y]\n"
      "adc r31, __zero_reg__\n"
      // load correct bitshift from program RAM
      "lpm %[bit], Z\n"
      : [row_offset] "=&x"(row_offset), // upper register (ANDI)
        [bit] "=r"(bit),
        [y] "+d"(y), // upper register (ANDI), must be writable
        "+z"(bsl)    // is modified to point to the proper shift array element
      : [width_offset] "r"((uint8_t)(WIDTH / 8)),
        [x] "r"((uint8_t)x)
      :);

  if (color) {
    sBuffer[row_offset] |= bit;
  }
  else {
    sBuffer[row_offset] &= ~bit;
  }
#endif
  return TRUE;
}

BOOL Graphics::drawPixel(WORD x, WORD y) {
  if (x & ~0x7f || y & ~0x3f) {
    return FALSE;
  }

  WORD row_offset;
  WORD bit;

#if FALSE
  uint8_t row = (uint8_t)y / 8;
  row_offset = (row * WIDTH) + (uint8_t)x;
  bit = _BV((uint8_t)y % 8);
  sBuffer[row_offset] |= bit;
#else
  // uint8_t row = (uint8_t)y / 8;
  // row_offset = (row*WIDTH) + (uint8_t)x;
  // bit = _BV((uint8_t)y % 8);

  // the above math can also be rewritten more simply as;
  //   row_offset = (y * WIDTH/8) & ~0b01111111 + (uint8_t)x;
  // which is what the below assembler does

  // local variable for the bitshift_left array pointer,
  // which can be declared a read-write operand
  volatile const UBYTE *bsl = bitshift_left;

  asm volatile(
      "mul %[width_offset], %A[y]\n"
      "movw %[row_offset], r0\n"
      "andi %A[row_offset], 0x80\n" // row_offset &= (~0b01111111);
      "clr __zero_reg__\n"
      "add %A[row_offset], %[x]\n"
      // mask for only 0-7
      "andi %A[y], 0x07\n"
      // Z += y
      "add r30, %A[y]\n"
      "adc r31, __zero_reg__\n"
      // load correct bitshift from program RAM
      "lpm %[bit], Z\n"
      : [row_offset] "=&x"(row_offset), // upper register (ANDI)
        [bit] "=r"(bit),
        [y] "+d"(y), // upper register (ANDI), must be writable
        "+z"(bsl)    // is modified to point to the proper shift array element
      : [width_offset] "r"((uint8_t)(WIDTH / 8)),
        [x] "r"((uint8_t)x)
      :);

  sBuffer[row_offset] |= bit;
#endif
  return TRUE;
}

#ifdef FAST_LINE_ENABLE
BOOL Graphics::drawLine(WORD x, WORD y, WORD x2, WORD y2) {
  const int PRECISION = 8;
  BOOL drawn = false;

#ifdef INLINE_PLOT
  WORD row_offset;
  UBYTE bit;
  UBYTE row;
#endif

  bool yLonger = false;
  WORD incrementVal, endVal;
  WORD shortLen = y2 - y;
  WORD longLen = x2 - x;

  if (abs(shortLen) > abs(longLen)) {
    swap(shortLen, longLen);
    yLonger = true;
  }

  endVal = longLen;

  if (longLen < 0) {
    incrementVal = -1;
    longLen = -longLen;
  }
  else {
    incrementVal = 1;
  }

  WORD decInc = longLen == 0 ? 0 : (shortLen << PRECISION) / longLen;
  WORD j = 0;
  if (yLonger) {
    for (WORD i = 0; i != endVal; i += incrementVal, j += decInc) {
#ifdef INLINE_PLOT
      WORD xx = x + (j >> PRECISION),
           yy = y + i;

      if (xx & ~0x7f || yy & ~0x3f) {
        continue;
      }
      drawn = TRUE;
      row = (uint8_t)yy / 8;
      row_offset = (row * WIDTH) + (uint8_t)xx;
      bit = _BV((UBYTE)yy % 8);
      sBuffer[row_offset] |= bit;
#else
      drawn |= drawPixel(x + (j >> PRECISION), y + i);
#endif
    }
  }
  else {
    for (WORD i = 0; i != endVal; i += incrementVal, j += decInc) {
#ifdef INLINE_PLOT
      WORD xx = x + i,
           yy = y + (j >> PRECISION);

      if (xx & ~0x7f || yy & ~0x3f) {
        continue;
      }
      drawn = TRUE;
      row = (uint8_t)yy / 8;
      row_offset = (row * WIDTH) + (uint8_t)xx;
      bit = _BV((UBYTE)yy % 8);
      sBuffer[row_offset] |= bit;
#else
      drawn |= drawPixel(x + i, y + (j >> PRECISION));
#endif
    }
  }
  return drawn;
}
#else
BOOL Graphics::drawLine(WORD x0, WORD y0, WORD x1, WORD y1) {
  BOOL drawn = false;

#ifdef INLINE_PLOT
  WORD row_offset;
  UBYTE bit;
  UBYTE row;
#endif
  // bresenham's algorithm - thx wikpedia
  BOOL steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  WORD dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  WORD err = dx / 2;
  BYTE ystep;

  if (y0 < y1) {
    ystep = 1;
  }
  else {
    ystep = -1;
  }

  if (steep) {
    for (; x0 <= x1; x0++) {
#ifdef INLINE_PLOT
      if (y0 & ~0x7f || x0 & ~0x3f) {
        continue;
      }
      drawn = TRUE;
      row = (uint8_t)x0 / 8;
      row_offset = (row * WIDTH) + (uint8_t)y0;
      bit = _BV((UBYTE)x0 % 8);
      sBuffer[row_offset] |= bit;
#else
      drawn |= drawPixel(y0, x0);
#endif
      err -= dy;
      if (err < 0) {
        y0 += ystep;
        err += dx;
      }
    }
  }
  else {
    for (; x0 <= x1; x0++) {
#ifdef INLINE_PLOT
      if (x0 & ~0x7f || y0 & ~0x3f) {
        continue;
      }
      drawn = TRUE;
      row = (uint8_t)y0 / 8;
      row_offset = (row * WIDTH) + (uint8_t)x0;
      bit = _BV((UBYTE)y0 % 8);
      sBuffer[row_offset] |= bit;
#else
      drawn |= drawPixel(x0, y0);
#endif
      err -= dy;
      if (err < 0) {
        y0 += ystep;
        err += dx;
      }
    }
  }
  return drawn;
}

#endif

BOOL Graphics::drawVectorGraphic(const BYTE *graphic, float x, float y, float theta, float scaleFactor) {
  graphic += 1;
  BYTE
      //    width = pgm_read_byte(graphic),
      //       height = pgm_read_byte(++graphic),
      numRows = pgm_read_byte(++graphic);
  BOOL drawn = false;

  float rad = float(theta) * 3.1415926 / 180,
        sint = sin(rad),
        cost = cos(rad);

  for (BYTE i = 0; i < numRows; i++) {
    float x0, y0, x1, y1;

    if (scaleFactor == 0) {
      x0 = ((BYTE)pgm_read_byte(++graphic) + x);
      y0 = ((BYTE)pgm_read_byte(++graphic) + y);
      x1 = ((BYTE)pgm_read_byte(++graphic) + x);
      y1 = ((BYTE)pgm_read_byte(++graphic) + y);
    }
    else {
      x0 = (BYTE)pgm_read_byte(++graphic);

      x0 = (x0 / scaleFactor + x);
      y0 = ((BYTE)pgm_read_byte(++graphic) / scaleFactor + y);
      x1 = ((BYTE)pgm_read_byte(++graphic) / scaleFactor + x);
      y1 = ((BYTE)pgm_read_byte(++graphic) / scaleFactor + y);
    }

    drawn |= drawLine(
        (x0 - x) * cost - (y0 - y) * sint + x,
        (y0 - y) * cost + (x0 - x) * sint + y,
        (x1 - x) * cost - (y1 - y) * sint + x,
        (y1 - y) * cost + (x1 - x) * sint + y);
  }
  return drawn;
}

void Graphics::explodeVectorGraphic(const BYTE *graphic, float x, float y, float theta, float scaleFactor, BYTE step) {
  graphic++;
  BYTE
      //    width = pgm_read_byte(graphic),
      //       height = pgm_read_byte(++graphic),
      numRows = pgm_read_byte(++graphic);

  float rad = float(theta) * 3.1415926 / 180,
        sint = sin(rad),
        cost = cos(rad);

  for (BYTE i = 0; i < numRows; i++) {

    float x0, y0, x1, y1;
    BYTE xx0 = pgm_read_byte(++graphic),
         yy0 = pgm_read_byte(++graphic),
         xx1 = pgm_read_byte(++graphic),
         yy1 = pgm_read_byte(++graphic);

    if (scaleFactor == 0) {
      x0 = xx0 + x;
      y0 = yy0 + y;
      x1 = xx1 + x;
      y1 = yy1 + y;
    }
    else {
      x0 = (xx0 / scaleFactor + x);
      y0 = (yy0 / scaleFactor + y);
      x1 = (xx1 / scaleFactor + x);
      y1 = (yy1 / scaleFactor + y);
    }

    x0 = x0 + (xx0 / 8) * step;
    y0 = y0 + (yy0 / 8) * step;
    x1 = x1 + (xx0 / 8) * step;
    y1 = y1 + (yy0 / 8) * step;

    drawLine(
        (x0 - x) * cost - (y0 - y) * sint + x,
        (y0 - y) * cost + (x0 - x) * sint + y,
        (x1 - x) * cost - (y1 - y) * sint + x,
        (y1 - y) * cost + (x1 - x) * sint + y);
  }
}

void Graphics::drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color) {
  // no need to draw at all if we're offscreen
  if (x + w < 0 || x > WIDTH - 1 || y + h < 0 || y > HEIGHT - 1)
    return;

  int yOffset = abs(y) % 8;
  int sRow = y / 8;
  if (y < 0) {
    sRow--;
    yOffset = 8 - yOffset;
  }
  int rows = h / 8;
  if (h % 8 != 0)
    rows++;
  for (int a = 0; a < rows; a++) {
    int bRow = sRow + a;
    if (bRow > (HEIGHT / 8) - 1)
      break;
    if (bRow > -2) {
      for (int iCol = 0; iCol < w; iCol++) {
        if (iCol + x > (WIDTH - 1))
          break;
        if (iCol + x >= 0) {
          if (bRow >= 0) {
            if (color == WHITE)
              sBuffer[(bRow * WIDTH) + x + iCol] |= pgm_read_byte(bitmap + (a * w) + iCol) << yOffset;
            else if (color == BLACK)
              sBuffer[(bRow * WIDTH) + x + iCol] &= ~(pgm_read_byte(bitmap + (a * w) + iCol) << yOffset);
            else
              sBuffer[(bRow * WIDTH) + x + iCol] ^= pgm_read_byte(bitmap + (a * w) + iCol) << yOffset;
          }
          if (yOffset && bRow < (HEIGHT / 8) - 1 && bRow > -2) {
            if (color == WHITE)
              sBuffer[((bRow + 1) * WIDTH) + x + iCol] |= pgm_read_byte(bitmap + (a * w) + iCol) >> (8 - yOffset);
            else if (color == BLACK)
              sBuffer[((bRow + 1) * WIDTH) + x + iCol] &= ~(pgm_read_byte(bitmap + (a * w) + iCol) >> (8 - yOffset));
            else
              sBuffer[((bRow + 1) * WIDTH) + x + iCol] ^= pgm_read_byte(bitmap + (a * w) + iCol) >> (8 - yOffset);
          }
        }
      }
    }
  }
}

void Graphics::fillScreen(UBYTE color) {
  // C version:
  //
  // if (color != BLACK)
  // {
  //   color = 0xFF; // all pixels on
  // }
  // for (int16_t i = 0; i < WIDTH * HEIGTH / 8; i++)
  // {
  //    sBuffer[i] = color;
  // }

  // This asm version is hard coded for 1024 bytes. It doesn't use the defined
  // WIDTH and HEIGHT values. It will have to be modified for a different
  // screen buffer size.
  // It also assumes color value for BLACK is 0.

  // local variable for screen buffer pointer,
  // which can be declared a read-write operand
  uint8_t *bPtr = sBuffer;

  asm volatile(
      // if value is zero, skip assigning to 0xff
      "cpse %[color], __zero_reg__\n"
      "ldi %[color], 0xFF\n"
      // counter = 0
      "clr __tmp_reg__\n"
      "loopto:\n"
      // (4x) push zero into screen buffer,
      // then increment buffer position
      "st Z+, %[color]\n"
      "st Z+, %[color]\n"
      "st Z+, %[color]\n"
      "st Z+, %[color]\n"
      // increase counter
      "inc __tmp_reg__\n"
      // repeat for 256 loops
      // (until counter rolls over back to 0)
      "brne loopto\n"
      : [color] "+d"(color),
        "+z"(bPtr)
      :
      :);
}
