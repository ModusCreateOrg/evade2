#include "Game.h"

WORD Camera::x = 0;
WORD Camera::y = 0;
FLOAT Camera::z = 0;

WORD Camera::vx = 0;
WORD Camera::vy = 0;
FLOAT Camera::vz = 0;

void Camera::move() {
  Camera::x += Camera::vx;
  Camera::y += Camera::vy;
  Camera::z += Camera::vz;
  if (Camera::x < MIN_CAMERA_X) {
    Camera::x = MIN_CAMERA_X;
  }
  if (Camera::x > MAX_CAMERA_X) {
    Camera::x = MAX_CAMERA_X;
  }
  if (Camera::y < MIN_CAMERA_Y) {
    Camera::y = MIN_CAMERA_Y;
  }
  if (Camera::y > MAX_CAMERA_Y) {
    Camera::y = MAX_CAMERA_Y;
  }
}
