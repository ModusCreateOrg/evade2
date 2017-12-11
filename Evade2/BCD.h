#ifndef BCD_H
#define BCD_H

#include "Types.h"

typedef ULONG BCD;

extern ULONG bcd_add(BCD x, BCD y);
// out must be at least 9 characters/bytes
extern void bcd_string(BCD in, char *out);

#endif
