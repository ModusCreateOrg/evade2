#ifndef DEBUG_H
#define DEBUG_H

#include "Game.h"

/**
 * Serial port debug(), printf() style.
 *
 * You can call debug(const char *fmt, ...) to print message to the serial port.
 *
 * Supported formats are:
 * %% = prints %
 * %b = prints next argument as binary
 * %x = prints next argument as hex
 * %f = prints next argument as float (not working?)
 * %d = prints next argument as string
 *
 * NOTES:
 *
 * 1) In Game.h, you must define DEV or all debug() will be removed from the game, period.
 * 2) In your .cpp file, you must define DEBUGME to turn on debug for that file.  For example:
 * #define DEBUGME
 */
#ifdef DEV
#ifdef DEBUGME
extern void _debug(const __FlashStringHelper *ifsh, ...);
#define debug(fmt, ...) _debug(F(fmt), ##__VA_ARGS__)
#else
#define debug(...)
#endif
#else
// if !DEV set, then we replace debug calls with empty macros to save space
#define debug(...)
#endif

#endif
