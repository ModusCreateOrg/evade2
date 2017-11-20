#include "Game.h"

static Process processes[NUM_PROCESSES];

static Process *alloc_process() {
  for (BYTE i = 0; i < NUM_PROCESSES; i++) {
    Process *p = &processes[i];
    if (!p->flags) {
      p->flags |= PFLAG_ACTIVE;
      return p;
    }
  }
  return NULL;
}

static void free_process(Process *p) {
  p->flags = 0;
}

void ProcessManager::init() {
  for (BYTE i = 0; i < NUM_PROCESSES; i++) {
    processes[i].flags = 0;
  }
}

void ProcessManager::genocide() {
  for (BYTE i = 0; i < NUM_PROCESSES; i++) {
    Process *p = &processes[i];

    if (p->type != PTYPE_SYSTEM) {
      p->flags = 0;
    }
  }
}

void ProcessManager::run() {
  for (BYTE i = 0; i < NUM_PROCESSES; i++) {
    Process *p = &processes[i];

    if (p->flags & PFLAG_ACTIVE) {
      if (--p->timer <= 0) {
        p->run(p);
      }
    }
  }
}

Process *ProcessManager::birth(void (*func)(Process *p), BYTE type) {
  Process *p = alloc_process();
  if (!p) {
    return NULL;
  }

  p->run = func;
  p->o = NULL;
  p->type = type;
  p->timer = 1; // wake up right away

  return p;
}

void ProcessManager::kill(Process *p) {
  if (p->o) {
    ObjectManager::free(p->o);
    p->o = NULL;
  }
  free_process(p);
}
