#ifndef PROCESS_H
#define PROCESS_H

#include "Game.h"

class ProcessManager;
class Object;

class Process {
  friend ProcessManager;

protected:
  Process *next;
  Process *prev;
  WORD timer;
  BYTE state;
  BYTE type;
  Object *o;

protected:
  void (*run)();
  void sleep(WORD time, void (*func)() = NULL);
  void suicide();
};

#endif
