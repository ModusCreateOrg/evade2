#include "Game.h"
#include "Object.h"

void Object::move() {
  x += vx;
  y += vy;
  z += vz;
}

void Object::draw() {
  // scale and render the lines
}
