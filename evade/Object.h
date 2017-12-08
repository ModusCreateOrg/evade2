#ifndef OBJECT_H
#define OBJECT_H

#include "Types.h"

class ObjectManager;
class Bullet;
class EBullet;

// Object is an enemy
#define OFLAG_ENEMY (1 << 0)
// Object is player's bullet
#define OFLAG_PLAYER_BULLET (1 << 1)
// Object is enemy bullet
#define OFLAG_ENEMY_BULLET (1 << 2)
// STRING means lines is a character string to be rendered in 3D
#define OFLAG_STRING (1 << 3)
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
  FLOAT x, y, z;    // coordinates
  FLOAT vx, vy, vz; // velocity in x,y,z
  BYTE flags;
  BYTE timer;
  WORD state; // arbitrary data byte for AI use (can be explosion step, etc.)
  WORD theta; // rotation around Z (in degrees, 0-60)

public:
  void move();
  void draw();
};

#endif
