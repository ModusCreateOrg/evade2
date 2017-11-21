#ifndef TYPES_H
#define TYPES_H

#include <Arduboy2.h>

typedef uint8_t UBYTE;
typedef int8_t BYTE;
typedef uint16_t UWORD;
typedef int16_t WORD;
typedef bool BOOL;
typedef void *APTR;
typedef WORD COORD;
typedef WORD FIXED;

#define fixed(i) (i << 4)
#define fint(f) (f >> 4)
#define fmul(a, b) ((a * b) >> 4)
#define fdiv(a, b) ((a << 4) / b)
#define fadd(a, b) (a + b)
#define fsub(a, b) (a - b)

#ifndef TRUE
#define TRUE (!0)
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL (void *)0
#endif

#endif
