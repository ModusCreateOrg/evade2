#ifndef PROCESS_H
#define PROCESS_H

#include "Game.h"

class Object;

class Process {
  friend ProcessManager;

protected:
  Process *next;

public:
  BYTE type;  // e.g. PTYPE_SYSTEM, PTYPE_USER
  BYTE timer; // number of ticks until wake up
              //  BYTE state; // a byte of state to be used by process logic for anything at all
  Object *o;

public:
  void (*run)(Process *me);
  void sleep(BYTE time, void (*func)(Process *me) = NULL);
  void suicide();
};

#endif
