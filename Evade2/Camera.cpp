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
