#define DEBUGME
//#undef DEBUGME

#include "Game.h"

BOOL EnemyBase::clipped(Object *o) {
  return (o->z < Camera::z);
}

BOOL EnemyBase::collide(Object *o) {
  if (o->flags & OFLAG_COLLISION) {
    o->state = 0;
    o->flags &= ~OFLAG_COLLISION;
    return TRUE;
  }
  return false;
}

void EnemyBase::bank(Object *o, WORD delta) {
  if (o->flags & OFLAG_BANK_LEFT) {
    o->theta -= DELTA_THETA;
    if (o->theta < -delta) {
      o->flags &= ~OFLAG_BANK_LEFT;
    }
  }
  else {
    o->theta += DELTA_THETA;
    if (o->theta > delta) {
      o->flags |= OFLAG_BANK_LEFT;
    }
  }
}

void EnemyBase::roll(Object *o) {
  if (o->flags & OFLAG_BANK_LEFT) {
    o->theta -= DELTA_THETA;
  }
  else {
    o->theta += DELTA_THETA;
  }
}

void EnemyBase::fire(Object *o) {
  o->state--;
  if (o->state <= 0) {
    if (Camera::vx || Camera::vy) {
      o->state = 1;
      return;
    }
    // fire!
    Process *p = ProcessManager::birth(EBullet::ebullet_process);
    if (p) {
      Object *bullet = ObjectManager::alloc();
      if (bullet) {
        bullet->x = o->x - 8;
        bullet->y = o->y - 8; //  - 32;
        bullet->z = o->z;
        p->o = bullet;
        o->state = FIRE_TIME;
      }
      else {
        ProcessManager::kill(p);
        o->state = 1;
      }
    }
  }
  else {
    o->state--;
  }
}
