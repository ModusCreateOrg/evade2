#define DEBUGME

#include "Evade2.h"

static Object objects[NUM_OBJECTS];
static Object *free_list = NULL,
              *active_list = NULL;

void ObjectManager::init() {
  for (BYTE i = 0; i < NUM_OBJECTS; i++) {
    objects[i].next = free_list;
    free_list = &objects[i];
  }
}

Object *ObjectManager::first() {
  return active_list;
}

void ObjectManager::run() {
  for (Object *o = active_list; o; o = o->next) {
    if (o->lines) {
      o->move();
      o->draw();
      // check collisions
      if (o->get_type() == OTYPE_ENEMY) {

        // JG: Removed /2 because it made it impossible to hit anything. Could be because the  hit box wasn't centered?
        // const UBYTE ow = (UBYTE)pgm_read_byte(o->lines) / 2,
        //             oh = (UBYTE)pgm_read_byte(o->lines + 1) / 2;
        const UBYTE ow = (UBYTE)pgm_read_byte(o->lines),
                    oh = (UBYTE)pgm_read_byte(o->lines + 1);

        for (Object *oo = active_list; oo && oo->next != o; oo = oo->next) {

          if (oo->get_type() == OTYPE_PLAYER_BULLET) {
            if (abs(o->z - oo->z) < BULLET_VZ && abs(o->x - oo->x) < ow && abs(o->y - oo->y) < oh) {
              oo->flags |= OFLAG_COLLISION;
              o->flags |= OFLAG_COLLISION;
              break; // only collide once!
            }
          }
        }
      }
    }
  }
}

Object *ObjectManager::alloc() {
  Object *o = free_list;
  if (o) {
    free_list = o->next;
    o->next = active_list;
    active_list = o;
    o->init();
  }
#ifdef DEV
  else {
    debug("ObjectManager alloc failed\n");
  }
#endif
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
