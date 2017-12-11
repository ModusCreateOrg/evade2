#include "Evade2.h"

static BCD median(BCD x, BCD y, BCD z) {
  return (x & (y | z)) | (y & z);
}

// From Knuth, TAOCP Vol. 4A, Part 1
BCD bcd_add(BCD x, BCD y) {
  BCD z, u, t;
  z = y + 0x66666666;
  u = x + z;
  t = median(~x, ~z, u) & 0x88888888;
  return u - t + (t >> 2);
}

// convert BCD (ULONG) to string
// the output string is provided by the caller and must be at least 9
// characters in length, 8 for the digits, 1 for the null terminator.
void bcd_string(BCD in, char *out) {
  for (BYTE i = 0; i < 8; i++) {
    out[7 - i] = (in & 0x0f) + '0';
    in >>= 4;
  }
  out[8] = '\0';
}
