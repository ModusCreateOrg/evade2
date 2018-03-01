#ifndef TYPES_H
#define TYPES_H

#include <Arduboy2Core.h>

typedef uint8_t UBYTE;
typedef int8_t BYTE;
typedef uint16_t UWORD;
typedef int16_t WORD;
typedef uint8_t BOOL;
typedef void *APTR;
typedef uint32_t ULONG;
typedef int32_t LONG;
typedef uint16_t FXP_ANGLE;
typedef uint16_t FXP_USCALE;
typedef int16_t FXP_SSCALE;
typedef int16_t FXP_WORLD_COORD;
typedef int8_t DISPLAY_S_COORD;

#ifndef TRUE
#define TRUE (!0)
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL (void *)0
#endif

#ifndef PI
#define PI 3.1415926
#endif

#ifndef RADIANS
#define RADIANS(degrees) ((degrees) * PI / 180)
#endif

#define FXP_RADIANS(degrees) ((UINT16_MAX/360)*(degrees))

#endif
