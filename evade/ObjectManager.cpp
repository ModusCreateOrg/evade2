#define DEBUGME
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
    // check collisions
    if (o->flags & OFLAG_ENEMY) {
      const BYTE ow = pgm_read_byte(o->lines) / 2,
                 oh = pgm_read_byte(o->lines + 1) / 2;

      for (Object *oo = active_list; oo && oo->next != o; oo = oo->next) {
        if (oo->flags & OFLAG_PLAYER_BULLET) {
          if (abs(o->z - oo->z) < BULLET_VZ && abs(o->x - oo->x) < ow && abs(o->y - oo->y) < oh) {
            oo->flags |= OFLAG_COLLISION;
            o->flags |= OFLAG_COLLISION;
          }
        }
      }
    }
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
  o->flags = 0;
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
