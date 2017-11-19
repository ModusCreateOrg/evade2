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

void debug(char *fmt, ...) {
  debug_init();

  va_list ap;
  char c;
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
            Serial.print(va_arg(ap, int));
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
