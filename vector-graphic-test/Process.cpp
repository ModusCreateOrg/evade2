#include "Game.h"

void Process::sleep(WORD time, void (*func)()) {
  this->timer = time;
  if (func) {
    this->run = func;
  }
}
void Process::suicide() {
  ProcessManager::kill(this);
}
