#ifndef PROCESS_H
#define PROCESS_H

#include "Game.h"

class Object;

#define PFLAG_ACTIVE (1 << 0)

class Process {
public:
  BYTE type, flags;
  WORD timer;
  Object *o;

public:
  void (*run)(Process *me);
  void sleep(WORD time, void (*func)(Process *me) = NULL);
  void suicide();
};

#endif
