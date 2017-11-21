#include "debug.h"
#include <stdarg.h>

#ifdef DEV

static BOOL initialized = FALSE;
static void debug_init() {
  if (!initialized) {
    Serial.begin(9600);
    initialized = TRUE;
  }
}

void _debug(const __FlashStringHelper *ifsh, ...) {
  va_list ap;
  char c;
  float f;
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  va_start(ap, ifsh);

  debug_init();
  while (1) {
    c = pgm_read_byte(p++);
    switch (c) {
      case '\0':
        va_end(ap);
        return;
      case '%':
        c = pgm_read_byte(p++);
        switch (c) {
          //          case '\0':
          va_end(ap);
          return;
          case '%':
            Serial.print('%');
            break;
          case 'b':
            Serial.print(va_arg(ap, int), BIN);
            break;
          case 'x':
            Serial.print(va_arg(ap, int) & 0xffff, HEX);
            break;
          case 'f':
            //            f = va_arg(ap, float);
            //            Serial.print(va_arg(ap, float));
            break;
          case 'd':
            Serial.print(va_arg(ap, int));
            break;
          default:
            Serial.print(c);
            break;
        }
        break;
      default:
        Serial.print(c);
        break;
    }
  }
  va_end(ap);
}

#if 0
void debug(char *fmt, ...) {
  debug_init();

  va_list ap;
  char c;
  float f;
  va_start(ap, fmt);

  while (c = *fmt++) {
    switch (c) {
      case '%':
        c = *fmt++;
        switch (c) {
          case '\0':
            va_end(ap);
            return;
          case '%':
            Serial.print('%');
            break;
          case 'b':
            Serial.print(va_arg(ap, int), BIN);
            break;
          case 'x':
            Serial.print(va_arg(ap, int) & 0xffff, HEX);
            break;
          case 'f':
            //            f = va_arg(ap, float);
            //            Serial.print(va_arg(ap, float));
            break;
          case 'd':
            Serial.print(va_arg(ap, int));
            break;
          default:
            Serial.print(c);
            break;
        }
        break;
      default:
        Serial.print(c);
        break;
    }
  }
  va_end(ap);
}
#endif

#endif
