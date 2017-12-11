#include "Evade2.h"

void Process::sleep(BYTE time, void (*func)(Process *me, Object *o)) {
  this->timer = time;
  if (func) {
    this->run = func;
  }
}

void Process::suicide() {
  ProcessManager::kill(this);
}
