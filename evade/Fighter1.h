#ifndef FIGHTER1_H
#define FIGHTER1_H

/**
 * Fighter1 process.
 *
 * We only expose the initial state/function as extern here, so it can be ProcessManager::birth()
 * from anywhere.
 *
 * The remaining states are static/local to the Fighter1.cpp file.
 */
extern void fighter1_process(Process *me);

#endif
