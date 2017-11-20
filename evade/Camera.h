#ifndef CAMERA_H
#define PCAMERA_HLAYER_H

#include "Types.h"

class Camera {
public:
  static COORD x, y, z;
  static COORD vx, vy, vz;

public:
  static void move();
};

#endif
