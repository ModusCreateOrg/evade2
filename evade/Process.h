#ifndef PROCESS_H
#define PROCESS_H

#include "Game.h"

class Object;

class Process {
public:
  Process *next;
  Process *prev;
  WORD timer;
  BYTE state;
  BYTE type;
  Object *o;

public:
  void (*run)(Process *me);
  void sleep(WORD time, void (*func)(Process *me) = NULL);
  void suicide();
};

#endif
