#ifndef OBJECT_H
#define OBJECT_H

#include "Types.h"

class ObjectManager;
class Bullet;
class EBullet;

#define OFLAG_TYPE_MASK (0x07)
// Object is an enemy
#define OTYPE_ENEMY 0
// Object is player's bullet
#define OTYPE_PLAYER_BULLET 1
// Object is enemy bullet
#define OTYPE_ENEMY_BULLET 2
// STRING means lines is a character string to be rendered in 3D
#define OTYPE_STRING 3
#define OTYPE_ASTEROID 4
// MOON means lines is ignored and a circle is rendered, as in a moon or planet
// theta becomes radius
#define OTYPE_MOON 5

// FLAGS
// if set, the lines will explode
#define OFLAG_EXPLODE (1 << 4)
// set when the object has collided (ENEMY vs PLAYER BULLET, etc.)
#define OFLAG_COLLISION (1 << 5)
// Process can use the remaining bits, starting with (1<<USER_BIT)
#define OFLAG_USER_BIT (6)

class Object {
  friend ObjectManager;
  friend Bullet;
  friend EBullet;

protected:
  Object *next;

protected:
  void init();

public:
  // if lines is NULL, then the variables in the Object structure can be used for any purpose
  const BYTE *lines;
  //
  FXP_WORLD_COORD x, y, z;    // coordinates
  FXP_WORLD_COORD vx, vy, vz; // velocity in x,y,z
  UBYTE flags;
  BYTE timer;
  WORD state; // arbitrary data byte for AI use (can be explosion step, etc.)
  FXP_ANGLE theta; // rotation around Z (in normalized fixed point radians)

public:
  inline void set_type(UBYTE type) {
    flags = (flags & ~OFLAG_TYPE_MASK) | type;
  }
  inline UBYTE get_type() {
    return flags & OFLAG_TYPE_MASK;
  }

public:
  void move();
  void draw();
};

#endif
