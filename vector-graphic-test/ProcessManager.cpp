#include "Game.h"

static Process processes[NUM_PROCESSES];
static Process *free_list, *active_list;

void ProcessManager::init() {
  for (BYTE i = 0; i < NUM_PROCESSES; i++) {
    Process *p = &processes[i];
    Process *next = (i == NUM_PROCESSES - 1) ? (Process *)&free_list : &processes[i + 1];
    Process *prev = (i == 0) ? (Process *)&free_list : &processes[i - 1];

    p->next = next;
    p->prev = prev;
    prev->next = p;
    next->prev = p;
  }
  active_list = NULL;
}

void ProcessManager::genocide() {
  for (Process *p = active_list; p;) {
    Process *next = p->next;
    if (p->type != PTYPE_SYSTEM) {
      ProcessManager::kill(p);
    }
    p = next;
  }
}

void ProcessManager::run() {
  for (Process *p = active_list; p;) {
    Process *next = p->next;
    if (!p->timer--) {
      p->run();
    }
    p = next;
  }
}

Process *ProcessManager::birth(void (*func)(), BYTE type) {
  Process *p = free_list;
  free_list = p->next;
  p->next = active_list;
  active_list->prev = p;
  p->prev = (Process *)&active_list;
  active_list = p;

  p->run = func;
  p->o = NULL;
  p->type = type;
  p->timer = 1; // wake up right away
  p->state = 0;

  return p;
}

void ProcessManager::kill(Process *p) {
  Process *prev = p->prev;
  Process *next = p->next;
  prev->next = next;
  next->prev = prev;
  p->next = free_list;
  p->prev = (Process *)&free_list;
  free_list = p;
}
