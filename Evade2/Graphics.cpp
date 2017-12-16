/**
 * Portions of this class were lifted from the Arduboy2 library/class.
 * See https://github.com/MLXXXp/Arduboy2
 */

#define DEBUGME
#include "Evade2.h"

static UBYTE sBuffer[WIDTH * HEIGHT / 8];

static inline void swap(WORD &a, WORD &b) {
  WORD temp = a;
  a = b;
  b = temp;
}

void Graphics::display(BOOL clear) {
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

BOOL Graphics::drawCircle(WORD x0, WORD y0, BYTE r) {
  //void Graphics::drawCircle(WORD x0, WORD y0, BYTE r) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0, y0 + r);
  drawPixel(x0, y0 - r);
  drawPixel(x0 + r, y0);
  drawPixel(x0 - r, y0);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    drawPixel(x0 + x, y0 + y);
    drawPixel(x0 - x, y0 + y);
    drawPixel(x0 + x, y0 - y);
    drawPixel(x0 - x, y0 - y);
    drawPixel(x0 + y, y0 + x);
    drawPixel(x0 - y, y0 + x);
    drawPixel(x0 + y, y0 - x);
    drawPixel(x0 - y, y0 - x);
  }
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

struct vec_segment_u8 {
  int8_t x0;
  int8_t y0;
  int8_t x1;
  int8_t y1;
};

BOOL Graphics::drawVectorGraphic(const BYTE *graphic, float x, float y, float theta, float scaleFactor) {
  return explodeVectorGraphic(graphic, x, y, theta, scaleFactor, 0);
}

BOOL Graphics::explodeVectorGraphic(const BYTE *graphic, float x, float y, float theta, float scaleFactor, BYTE step) {
  graphic += 2;
  BOOL drawn = false;
  BYTE
      //    width = pgm_read_byte(graphic),
      //       height = pgm_read_byte(++graphic),
      numRows = pgm_read_byte(graphic++);

  float rad = float(theta) * 3.1415926 / 180,
        sint = sin(rad),
        cost = cos(rad);

  for (BYTE i = 0; i < numRows; i++) {
    struct vec_segment_u8 seg;
    float x0, y0, x1, y1;

    memcpy_P(&seg, graphic, sizeof(seg));
    graphic += sizeof(seg);

    x0 = seg.x0;
    y0 = seg.y0;
    x1 = seg.x1;
    y1 = seg.y1;

    if (scaleFactor) {
      x0 /= scaleFactor;
      y0 /= scaleFactor;
      x1 /= scaleFactor;
      y1 /= scaleFactor;
    }

    if (step) {
      x0 = x0 + (seg.x0 / 8) * step;
      y0 = y0 + (seg.y0 / 8) * step;
      x1 = x1 + (seg.x0 / 8) * step;
      y1 = y1 + (seg.y0 / 8) * step;
    }

    drawn |= drawLine(
        x0 * cost - y0 * sint + x,
        y0 * cost + x0 * sint + y,
        x1 * cost - y1 * sint + x,
        y1 * cost + x1 * sint + y);
  }
  return drawn;
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
          const uint8_t bmp_bits = pgm_read_byte(bitmap + (a * w) + iCol);
          if (bRow >= 0) {
            if (color == WHITE)
              sBuffer[(bRow * WIDTH) + x + iCol] |= bmp_bits << yOffset;
            else if (color == BLACK)
              sBuffer[(bRow * WIDTH) + x + iCol] &= ~(bmp_bits << yOffset);
            else
              sBuffer[(bRow * WIDTH) + x + iCol] ^= bmp_bits << yOffset;
          }
          if (yOffset && bRow < (HEIGHT / 8) - 1 && bRow > -2) {
            if (color == WHITE)
              sBuffer[((bRow + 1) * WIDTH) + x + iCol] |= bmp_bits >> (8 - yOffset);
            else if (color == BLACK)
              sBuffer[((bRow + 1) * WIDTH) + x + iCol] &= ~(bmp_bits >> (8 - yOffset));
            else
              sBuffer[((bRow + 1) * WIDTH) + x + iCol] ^= bmp_bits >> (8 - yOffset);
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
