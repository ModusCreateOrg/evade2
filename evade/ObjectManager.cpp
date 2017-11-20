#include "Game.h"

static Object objects[NUM_OBJECTS];

void ObjectManager::init() {
  for (BYTE i = 0; i < NUM_OBJECTS; i++) {
    objects[i].flags = 0;
  }
}

void ObjectManager::run() {
  for (BYTE i = 0; i < NUM_OBJECTS; i++) {
    Object *o = &objects[i];
    if (o->flags & OFLAG_ACTIVE) {
      o->move();
      o->draw();
    }
  }
}

Object *ObjectManager::alloc() {
  for (BYTE i = 0; i < NUM_OBJECTS; i++) {
    Object *o = &objects[i];
    if (!o->flags) {
      o->flags |= OFLAG_ACTIVE;
      return o;
    }
  }
  return NULL;
}

void ObjectManager::free(Object *o) {
  o->flags = 0;
}
