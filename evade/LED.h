#ifndef LED_H
#define LED_H

#include "Types.h"

class LED {
public:
  static void animate();
  static void rgb(BYTE r, BYTE g, BYTE b);
};

#endif
