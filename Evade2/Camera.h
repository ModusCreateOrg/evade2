#ifndef CAMERA_H
#define PCAMERA_HLAYER_H

#include "Types.h"

class Object;

class Camera {
public:
  static FXP_WORLD_COORD x, y, z;
  static FXP_WORLD_COORD vx, vy, vz;

public:
  static void move();
public:
  static BOOL collides_with(Object *o);
};

#endif
