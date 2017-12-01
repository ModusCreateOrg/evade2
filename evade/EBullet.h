#ifndef EBULLET_H
#define EBULLET_H

#include "Process.h"

class EBullet {
public:
  static void ebullet_process(Process *me);

private:
  static void wait(Process *me);
};

#endif
