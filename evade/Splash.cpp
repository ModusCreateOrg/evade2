#include "Game.h"

void Splash::start_game(Process *me) {
  ProcessManager::birth(Player::player_process, PTYPE_SYSTEM);
  ProcessManager::birth(Fighter1::fighter1_process);
  me->suicide();
}

void Splash::get_ready(Process *me) {
  printer.setCursor(35, 30);
  printer.setTextSize(1);
  printer.print(F("Get Ready!"));
  if (frameCounter > 45) {
    Splash::start_game(me);
  }
  else {
    me->sleep(1);
  }
}

void Splash::splash_process(Process *me) {
  Player::life = Player::power = -1;
  Camera::vz = CAMERA_VZ;
  printer.setCursor(25, 10);
  printer.setTextSize(2);
  printer.print(F("EVADE 2"));
  if (Controls::debounced(BUTTON_A)) {
    frameCounter = 0;
    me->sleep(1, Splash::get_ready);
    return;
  }
  else if (frameCounter & (1 << 4)) {
    printer.setCursor(15, 50);
    printer.setTextSize(1);
    printer.print(F("Press A to start"));
  }
  me->sleep(1);
}
