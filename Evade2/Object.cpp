#define DEBUGME

#include "Evade2.h"

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

  FXP_WORLD_COORD zz = (z - Camera::z) * 2;
  float ratio = 128 / (float(zz) + 128);

  register float cx = (Camera::x - x) * ratio + SCREEN_WIDTH / 2;
  register float cy = (Camera::y - y) * ratio + SCREEN_HEIGHT / 2;

  if (flags & OFLAG_EXPLODE) {
    Graphics::explodeVectorGraphic(lines, cx, cy, theta, 1 / ratio, state);
  }
  else {
    if (!Graphics::drawVectorGraphic(lines, cx, cy, theta, 1 / ratio) && (get_type() == OTYPE_ENEMY)) {
      // draw radar blip
      float dx = Camera::x - x,
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
