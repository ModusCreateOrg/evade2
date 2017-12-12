#ifndef PROCESS_H
#define PROCESS_H

#include "Evade2.h"

class Object;

class Process {
  friend ProcessManager;

protected:
  Process *next;

public:
  BYTE timer; // number of ticks until wake up
  Object *o;
  void (*run)(Process *me, Object *o);

public:
  void sleep(BYTE time, void (*func)(Process *me, Object *o) = NULL);
  void suicide();
};

#endif
