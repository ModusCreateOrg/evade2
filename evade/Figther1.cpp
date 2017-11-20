#include "Game.h"

#include "fighter1_img.h"

static void init(Object *o) {
  o->x = Camera::x; // 64 - (COORD)random(0, 128) + Camera::x;
  o->y = Camera::y; // 32 - (COORD)random(0, 64) + Camera::y;
  o->z = Camera::z; // (COORD)random(200, 255);
  o->vz = 6;
}
static void wait(Process *me) {
  Object *o = me->o;

  if (o->z > (Camera::z + 1024)) {
    init(o);
  }
  me->sleep(1, wait);
}

void fighter1_process(Process *me) {
  Object *o = ObjectManager::alloc();
  me->o = o;
  o->lines = fighter1_img;
  init(o);
  me->sleep(1, wait);
}
