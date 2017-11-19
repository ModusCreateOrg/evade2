#ifndef DEBUG_H
#define DEBUG_H

#include "Game.h"

#ifdef DEV
extern void debug(char *fmt, ...);
#else
// if !DEV set, then we replace debug calls with empty macros to save space
#define debug(...)
#endif

#endif
