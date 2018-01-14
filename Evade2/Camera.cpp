#include "Evade2.h"

FXP_WORLD_COORD Camera::x = 0;
FXP_WORLD_COORD Camera::y = 0;
FXP_WORLD_COORD Camera::z = 0;

FXP_WORLD_COORD Camera::vx = 0;
FXP_WORLD_COORD Camera::vy = 0;
FXP_WORLD_COORD Camera::vz = 0;

void Camera::move() {
  Camera::x += Camera::vx;
  Camera::y += Camera::vy;
  Camera::z += Camera::vz;
}

// return TRUE if o collides with player
BOOL Camera::collides_with(Object *o) {
  // If enemy bullet collides with player
  if (abs(o->z - Camera::z) < abs(o->vz) && abs(o->x - Camera::x) < 64 && abs(o->y - Camera::y) < 64) {
    return TRUE;
  }
  return FALSE;
}
