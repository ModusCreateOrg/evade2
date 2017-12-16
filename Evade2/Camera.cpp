#include "Evade2.h"

FLOAT Camera::x = 0;
FLOAT Camera::y = 0;
FLOAT Camera::z = 0;

FLOAT Camera::vx = 0;
FLOAT Camera::vy = 0;
FLOAT Camera::vz = 0;

void Camera::move() {
  Camera::x += Camera::vx;
  Camera::y += Camera::vy;
  Camera::z += Camera::vz;
}

// return TRUE if o collides with player
BOOL Camera::collides_with(Object *o) {
  // If enemy bullet collides with player
  if (abs(o->z - Camera::z) < abs(o->vz) && abs(o->x - Camera::x) < 128 && abs(o->y - Camera::y) < 64) {
    return TRUE;
  }
  return FALSE;
}
