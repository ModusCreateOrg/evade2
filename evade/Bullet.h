#ifndef BULLET_H
#define BULLET_H

// bullet process entrypoint
#include "Process.h"

class Bullet {
public:
  static void bullet_process(Process *p);

private:
  // states
  static void wait(Process *p);
};

#endif
