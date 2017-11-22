#include "Game.h"

static Object objects[NUM_OBJECTS];
static Object *free_list = NULL,
              *active_list = NULL;

void ObjectManager::init() {
  for (BYTE i = 0; i < NUM_OBJECTS; i++) {
    objects[i].next = free_list;
    free_list = &objects[i];
  }
}

void ObjectManager::run() {
  for (Object *o = active_list; o; o = o->next) {
    o->move();
    o->draw();
  }
}

#ifdef SMART_ERASE
void ObjectManager::erase() {
  for (Object *o = active_list; o; o = o->next) {
    o->erase();
  }
}
#endif

Object *ObjectManager::alloc() {
  Object *o = free_list;
  if (o) {
    free_list = o->next;
    o->next = active_list;
    active_list = o;
  }
  return o;
}

void ObjectManager::free(Object *o) {
  if (o) {
    if (active_list == o) {
      active_list = o->next;
      o->next = free_list;
      free_list = o;
    }
    else {
      for (Object *p = active_list; p; p = p->next) {
        if (p->next == o) {
          p->next = o->next;
          o->next = free_list;
          free_list = o;
          break;
        }
      }
    }
  }
}
