#include "Game.h"

static void start_game(Process *me) {
  HUD::setLife(random(0, 13));
  HUD::setPower(random(0, 13));
  ProcessManager::birth(player_process, PTYPE_SYSTEM);
  ProcessManager::birth(fighter1_process);
  me->suicide();
}

static void get_ready(Process *me) {
  arduboy.setCursor(35, 30);
  arduboy.setTextSize(1);
  arduboy.print(F("Get Ready!"));
  if (frameCounter > 45) {
    start_game(me);
  }
  else {
    me->sleep(1);
  }
}

void splash_process(Process *me) {
  HUD::setLife(-1);
  HUD::setPower(-1);
  Camera::vz = CAMERA_VZ;
  arduboy.setCursor(25, 10);
  arduboy.setTextSize(2);
  arduboy.print(F("EVADE 2"));
  if (Controls::debounced(BUTTON_A)) {
    frameCounter = 0;
    me->sleep(1, get_ready);
    return;
  }
  else if (frameCounter & (1 << 4)) {
    arduboy.setCursor(15, 50);
    arduboy.setTextSize(1);
    arduboy.print(F("Press A to start"));
  }
  me->sleep(1);
}
