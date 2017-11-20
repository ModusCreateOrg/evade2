#include "Game.h"

COORD Camera::x = 0;
COORD Camera::y = 0;
COORD Camera::z = 0;

COORD Camera::vx = 0;
COORD Camera::vy = 0;
COORD Camera::vz = 0;

void Camera::move() {
  Camera::x += Camera::vx;
  Camera::y += Camera::vy;
  Camera::z += Camera::vz;
}
