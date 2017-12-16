#ifndef CAMERA_H
#define PCAMERA_HLAYER_H

#include "Types.h"

class Object;

class Camera {
public:
  static FLOAT x, y;
  static FLOAT z;
  static FLOAT vx, vy;
  static FLOAT vz;

public:
  static void move();
public:
  static BOOL collides_with(Object *o);
};

#endif
