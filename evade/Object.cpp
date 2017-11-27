#define DEBUGME
#include "Game.h"

void Object::move() {
  x += vx;
  y += vy;
  z += vz;
}

void Object::draw() {
  float zz = (z - Camera::z) * 2;
  float ratio = 128 / (zz + 128);

  register float cx = (Camera::x - x) * ratio + SCREEN_WIDTH / 2;
  register float cy = (Camera::y - y) * ratio + SCREEN_HEIGHT / 2;

  //drawVectorGraphic(lines, cx, cy, float(theta), 1 / ratio);
  if (step > 0) {
    Graphics::explodeVectorGraphic(lines, cx, cy, float(theta), 1 / ratio, step);
  }
  else {
    Graphics::drawVectorGraphic(lines, cx, cy, float(theta), 1 / ratio);
  }
}

#ifdef SMART_ERASE
void Object::erase() {
  float zz = (z - Camera::z) * 2;
  float ratio = 128 / (zz + 128);

  register float cx = (Camera::x - x) * ratio + SCREEN_WIDTH / 2;
  register float cy = (Camera::y - y) * ratio + SCREEN_HEIGHT / 2;

  Graphics::eraseVectorGraphic(lines, cx, cy, float(theta), 1 / ratio);
}
#endif
