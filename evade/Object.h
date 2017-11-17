#ifndef OBJECT_H
#define OBJECT_H

#include "Types.h"

class Object {
public:
  Object *next, *prev; // linked list pointers
  float x, y, z;       // coordinates
  float vx, vy, vz;    // velocity in x,y,z
  int sx, sy;          // screen coordinates
  UBYTE type, mask;
  unsigned char *lines;

public:
  void move();
  void draw();
};

#endif
