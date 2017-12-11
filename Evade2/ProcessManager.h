#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include "Evade2.h"

class ProcessManager {
public:
  static Process *active_process;

public:
  static void init();
  static void genocide();
  static void run();
  static Process *birth(void (*func)(Process *me, Object *o), BOOL object = TRUE);
  static void kill(Process *p);

protected:
  static Process *alloc();
  static void free(Process *p);
};

#endif
