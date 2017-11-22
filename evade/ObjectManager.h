#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Game.h"

class ObjectManager {
public:
  static void init();
  static void run();
#ifdef SMART_ERASE
  static void erase();
#endif
  static Object *alloc();
  static void free(Object *o);
};
#endif
