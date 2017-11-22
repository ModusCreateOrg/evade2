#define DEBUGME
//#undef DEBUGME

#include "Game.h"

static void loop(Process *me) {
  if (Controls::debounced(BUTTON_A)) {
    ProcessManager::birth(bullet_process);
  }

  //  if (arduboy.pressed(B_BUTTON)) {
  //    vz += .1;
  //    if (vz > 25) {
  //      vz = 25;
  //    }
  //  }
  if (Controls::pressed(JOYSTICK_RIGHT)) {
    Camera::vx = -DELTACONTROL;
  }
  else if (Controls::pressed(JOYSTICK_LEFT)) {
    Camera::vx = DELTACONTROL;
  }
  else {
    Camera::vx = 0;
  }

  if (Controls::pressed(JOYSTICK_DOWN)) {
    Camera::vy = DELTACONTROL;
  }
  else if (Controls::pressed(JOYSTICK_UP)) {
    Camera::vy = -DELTACONTROL;
  }
  else {
    Camera::vy = 0;
  }

  me->sleep(1, loop);
}

void player_process(Process *me) {
  // initialize
  Camera::vz = CAMERA_VZ;
  me->sleep(1, loop);
}
