#ifndef CAMERA_H
#define PCAMERA_HLAYER_H

#include "Types.h"

class Camera {
public:
  static FLOAT x, y;
  static FLOAT z;
  static FLOAT vx, vy;
  static FLOAT vz;

public:
  static void move();
};

#endif
