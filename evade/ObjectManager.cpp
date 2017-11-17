#include "Game.h"

static Object objects[NUM_OBJECTS];
static Object *free_list, *active_list;

void ObjectManager::init() {
  for (BYTE i = 0; i < NUM_OBJECTS; i++) {
    Object *o = &objects[i];
    Object *next = (i == NUM_OBJECTS - 1) ? (Object *)&free_list : &objects[i + 1];
    Object *prev = (i == 0) ? (Object *)&free_list : &objects[i - 1];

    o->next = next;
    o->prev = prev;
    prev->next = o;
    next->prev = o;
  }
  active_list = NULL;
}

void ObjectManager::run() {
  for (Object *o = active_list; o; o = o->next) {
    o->move();
    o->draw();
  }
}

Object *ObjectManager::alloc() {
  Object *o = free_list;
  free_list = o->next;
  o->next = active_list;
  active_list->prev = o;
  o->prev = (Object *)&active_list;
  active_list = o;

  return o;
}

void ObjectManager::free(Object *o) {
  Object *prev = o->prev;
  Object *next = o->next;
  prev->next = next;
  next->prev = prev;
  o->next = free_list;
  o->prev = (Object *)&free_list;
  free_list = o;
}
