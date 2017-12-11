#define DEBUGME
#include "Game.h"

#include "img/radar_blip_img.h"

void Object::init() {
  x = y = z = 0;
  vx = vy = vz = 0;
  flags = state = timer = theta = 0;
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
    if (!Graphics::drawVectorGraphic(lines, cx, cy, FLOAT(theta), 1 / ratio) && (flags & OFLAG_ENEMY)) {
      // draw radar blip
      FLOAT dx = Camera::x - x,
            dy = Camera::y - y,
            angle = atan2(dy, dx);

      Graphics::drawVectorGraphic(
          radar_blip_img,
          SCREEN_WIDTH / 2 + cos(angle) * 32,
          SCREEN_HEIGHT / 2 + sin(angle) * 32,
          0,
          1);
    }
  }
}
