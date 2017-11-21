#define DEBUGME
#undef DEBUGME

#include "Game.h"

static Process processes[NUM_PROCESSES];
static Process *free_list = NULL,
               *active_list = NULL;

Process *ProcessManager::active_process = NULL;

Process *ProcessManager::alloc() {
  Process *p = free_list;
  if (p) {
    free_list = p->next;
    if (active_process) {
      p->next = active_process;
      active_process->next = p;
    }
    else {
      p->next = active_list;
      active_list = p;
    }
  }
  return p;
}

void ProcessManager::free(Process *p) {
  if (p) {
    if (active_list == p) {
      active_list = p->next;
      p->next = free_list;
      free_list = p;
    }
    else {
      for (Process *prev = active_list; prev; prev = prev->next) {
        if (prev->next == p) {
          prev->next = p->next;
          p->next = free_list;
          free_list = p;
          break;
        }
      }
    }
    debug("freed\n");
  }
}

void ProcessManager::init() {
  for (BYTE i = 0; i < NUM_PROCESSES; i++) {
    processes[i].next = free_list;
    free_list = &processes[i];
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
  for (active_process = active_list; active_process;) {
    Process *next = active_process->next;
    if (--active_process->timer <= 0) {
      active_process->run(active_process);
    }
    active_process = next;
  }
}

Process *ProcessManager::birth(void (*func)(Process *p), BYTE type) {
  Process *p = alloc();
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
  free(p);
}
