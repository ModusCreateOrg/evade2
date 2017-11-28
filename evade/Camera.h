#ifndef CAMERA_H
#define PCAMERA_HLAYER_H

#include "Types.h"

class Camera {
public:
  static WORD x, y;
  static FLOAT z;
  static WORD vx, vy;
  static FLOAT vz;

public:
  static void move();
};

#endif
