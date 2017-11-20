#ifndef OBJECT_H
#define OBJECT_H

#include "Types.h"

class Object {
public:
  Object *next, *prev; // linked list pointers
  COORD x, y, z;       // coordinates
  COORD vx, vy, vz;    // velocity in x,y,z
  WORD sx, sy;         // screen coordinates
  UBYTE type, mask;
  const UBYTE *lines;

public:
  void move();
  void draw();
};

#endif
