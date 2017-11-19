#include "Game.h"
#include "Object.h"

void Object::move() {
  x += vx;
  y += vy;
  z += vz;
}

void Object::draw() {
  // calculate width,height of viewing pyrmid at distance from camera in z
  COORD zz = (z - Camera::z) * 2;
  COORD width = zz + WIDTH;
  COORD height = zz + HEIGHT;
  float ratioX = WIDTH / width;
  float ratioY = HEIGHT / height;
}
