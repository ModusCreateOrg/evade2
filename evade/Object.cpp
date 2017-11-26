#define DEBUGME
#include "Game.h"
#include "Object.h"

#define INLINE_PLOT
//#undef INLINE_PLOT

static inline void swap(WORD &a, WORD &b) {
  WORD temp = a;
  a = b;
  b = temp;
}

void Object::move() {
  x += vx;
  y += vy;
  z += vz;
}

#ifndef INLINE_PLOT
static inline void drawPixel(WORD x, WORD y) {
  static const uint8_t bitshift_left[] PROGMEM = {
    _BV(0), _BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7)
  };

  if (x & ~0x7f || y & ~0x3f) {
    return;
  }
  //  if (x < 0 || x > (WIDTH - 1) || y < 0 || y > (HEIGHT - 1)) {
  //    debug("x %x y %x\n", x & ~0x7f, y & ~0x3f);
  //    return;
  //  }

  WORD row_offset;
  WORD bit;

#if TRUE
  uint8_t row = (uint8_t)y / 8;
  row_offset = (row * WIDTH) + (uint8_t)x;
  bit = _BV((uint8_t)y % 8);
  arduboy.sBuffer[row_offset] |= bit;
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

  arduboy.sBuffer[row_offset] |= bit;
#endif
}
#endif

void drawLine(WORD x, WORD y, WORD x2, WORD y2) {
  const int PRECISION = 8;

#ifdef INLINE_PLOT
  WORD row_offset;
  UBYTE bit;
  UBYTE row;
  register UBYTE *sBuffer = arduboy.sBuffer;
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
      row = (uint8_t)yy / 8;
      row_offset = (row * WIDTH) + (uint8_t)xx;
      bit = _BV((UBYTE)yy % 8);
      sBuffer[row_offset] |= bit;
#else
      drawPixel(x + (j >> PRECISION), y + i);
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
      row = (uint8_t)yy / 8;
      row_offset = (row * WIDTH) + (uint8_t)xx;
      bit = _BV((UBYTE)yy % 8);
      arduboy.sBuffer[row_offset] |= bit;
#else
      drawPixel(x + i, y + (j >> PRECISION));
#endif
    }
  }
}

#ifdef SMART_ERASE
void eraseLine(WORD x, WORD y, WORD x2, WORD y2) {
  const int PRECISION = 8;

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
      row = (uint8_t)yy / 8;
      row_offset = (row * WIDTH) + (uint8_t)xx;
      bit = _BV((UBYTE)yy % 8);
      arduboy.sBuffer[row_offset] &= ~bit;
#else
      drawPixel(x + (j >> PRECISION), y + i);
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
      row = (uint8_t)yy / 8;
      row_offset = (row * WIDTH) + (uint8_t)xx;
      bit = _BV((UBYTE)yy % 8);
      arduboy.sBuffer[row_offset] &= ~bit;
#else
      drawPixel(x + i, y + (j >> PRECISION));
#endif
    }
  }
}
#endif

static void drawVectorGraphic(const uint8_t *graphic, float x, float y, float theta, float scaleFactor) {

  // // Can't do anything here.
  // if (scaleFactor == 0) {
  //   return;
  // }

  byte width = pgm_read_byte(graphic),
       height = pgm_read_byte(++graphic);

  float imgCtrWidth = (width / scaleFactor) / 2,
        imgCtrHeight = (height / scaleFactor) / 2;

  byte numRows = pgm_read_byte(++graphic);

  float rad = float(theta) * 3.1415926 / 180,
        sint = sin(rad),
        cost = cos(rad);

  for (byte i = 0; i < numRows; i++) {

    float x0, y0, x1, y1;

    if (scaleFactor > 0) {
          x0 = (pgm_read_byte(++graphic) / scaleFactor + x) - imgCtrWidth;
          y0 = (pgm_read_byte(++graphic) / scaleFactor + y) - imgCtrHeight;
          x1 = (pgm_read_byte(++graphic) / scaleFactor + x) - imgCtrWidth;
          y1 = (pgm_read_byte(++graphic) / scaleFactor + y) - imgCtrHeight;
    }
    else if (scaleFactor == 0) {
          x0 = (pgm_read_byte(++graphic) + x) - imgCtrWidth;
          y0 = (pgm_read_byte(++graphic) + y) - imgCtrHeight;
          x1 = (pgm_read_byte(++graphic) + x) - imgCtrWidth;
          y1 = (pgm_read_byte(++graphic) + y) - imgCtrHeight;      
    }

    drawLine(
        (x0 - x) * cost - (y0 - y) * sint + x,
        (y0 - y) * cost + (x0 - x) * sint + y,
        (x1 - x) * cost - (y1 - y) * sint + x,
        (y1 - y) * cost + (x1 - x) * sint + y);
  }
}

#ifdef SMART_ERASE
static void eraseVectorGraphic(const uint8_t *graphic, float x, float y, float theta, float scaleFactor) {

  // Can't do anything here.
  if (scaleFactor == 0) {
    return;
  }

  byte width = pgm_read_byte(graphic),
       height = pgm_read_byte(++graphic);

  float imgCtrWidth = (width / scaleFactor) / 2,
        imgCtrHeight = (height / scaleFactor) / 2;

  byte numRows = pgm_read_byte(++graphic);

  float rad = float(theta) * 3.1415926 / 180,
        sint = sin(rad),
        cost = cos(rad);

  for (byte i = 0; i < numRows; i++) {

    float x0 = (pgm_read_byte(++graphic) / scaleFactor + x) - imgCtrWidth,
          y0 = (pgm_read_byte(++graphic) / scaleFactor + y) - imgCtrHeight,
          x1 = (pgm_read_byte(++graphic) / scaleFactor + x) - imgCtrWidth,
          y1 = (pgm_read_byte(++graphic) / scaleFactor + y) - imgCtrHeight;

    eraseLine(
        (x0 - x) * cost - (y0 - y) * sint + x,
        (y0 - y) * cost + (x0 - x) * sint + y,
        (x1 - x) * cost - (y1 - y) * sint + x,
        (y1 - y) * cost + (x1 - x) * sint + y);
  }
}
#endif

void Object::draw() {
  float zz = (z - Camera::z) * 2;
  float ratio = 128 / (zz + 128);

  register float cx = (Camera::x - x) * ratio + SCREEN_WIDTH / 2;
  register float cy = (Camera::y - y) * ratio + SCREEN_HEIGHT / 2;

  drawVectorGraphic(lines, cx, cy, float(theta), 1 / ratio);
}

#ifdef SMART_ERASE
void Object::erase() {
  float zz = (z - Camera::z) * 2;
  float ratio = 128 / (zz + 128);

  register float cx = (Camera::x - x) * ratio + SCREEN_WIDTH / 2;
  register float cy = (Camera::y - y) * ratio + SCREEN_HEIGHT / 2;

  eraseVectorGraphic(lines, cx, cy, float(theta), 1 / ratio);
}
#endif
