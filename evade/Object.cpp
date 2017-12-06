#define DEBUGME
#include "Game.h"

void Object::init() {
  x = y = z = 0;
  vx = vy = vz = 0;
  flags = state = theta = 0;
  lines = NULL;
}

void Object::move() {
  x += vx;
  y += vy;
  z += vz;
}

void Object::draw() {
  if (!lines || z <= Camera::z) {
    // nothing to draw
    return;
  }

  FLOAT zz = (z - Camera::z) * 2;
  FLOAT ratio = 128 / (zz + 128);

  register FLOAT cx = (Camera::x - x) * ratio + SCREEN_WIDTH / 2;
  register FLOAT cy = (Camera::y - y) * ratio + SCREEN_HEIGHT / 2;

  if (flags & OFLAG_EXPLODE) {
    Graphics::explodeVectorGraphic(lines, cx, cy, FLOAT(theta), 1 / ratio, state);
  }
  else {
    Graphics::drawVectorGraphic(lines, cx, cy, FLOAT(theta), 1 / ratio);
  }
}
