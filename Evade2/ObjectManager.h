#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Evade2.h"

class ObjectManager {
public:
  static void init();
  static void run();

public:
  static Object *alloc();
  static void free(Object *o);

public:
  // return 1st object in active list
  static Object *first();
};
#endif
