#include "utils.h"

char *itos(char *buf, int16_t val, uint8_t dig, char pad) {
  char *str = buf;
  uint8_t minus = val < 0 ? 1 : 0;

  val = minus ? -val : val;
  str += dig;

  for (; dig > 0; dig--) {
    str--;
    *str = "0123456789"[val % 10];
    val /= 10;
    if (!val)
      break;
  }
  for (dig--; dig > 0; dig--) {
    str--;
    if (minus) {
      minus = 0;
      *str = '-';
    } else
      *str = pad;
  }
  return str;
}
