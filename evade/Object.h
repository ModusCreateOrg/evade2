#ifndef OBJECT_H
#define OBJECT_H

#include "Types.h"

class ObjectManager;

// Object is an enemy
#define OFLAG_ENEMY (1 << 0)
// Object is player's bullet
#define OFLAG_PLAYER_BULLET (1 << 1)
// Object is enemy bullet
#define OFLAG_ENEMY_BULLET (1 << 2)
// STRING means lines is a character string to be rendered in 3D
#define OFLAG_STRING (1 << 3)
// set when the object has collided (ENEMY vs PLAYER BULLET, etc.)
#define OFLAG_COLLISION (1 << 4)
// Process can use the remaining bits, starting with (1<<USER_BIT)
#define OFLAG_USER_BIT (5)

class Object {
  friend ObjectManager;

protected:
  Object *next;

public:
  COORD x, y, z;    // coordinates
  COORD vx, vy, vz; // velocity in x,y,z
  BYTE flags;
  BYTE step;  // step of explosion animation, -1 = not exploding
  WORD theta; // rotation around Z (in degrees, 0-60)
  const BYTE *lines;

public:
  void move();
  void draw();
  void erase();
};

#endif
