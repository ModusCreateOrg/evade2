#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "Game.h"

class Process;

class ProcessManager {
public:
  static void init();
  static void genocide();
  static void run();
  static Process *birth(void (*func)(), BYTE type = PTYPE_USER);
  static void kill(Process *p);
};
#endif
