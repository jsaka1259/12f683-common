#include "utils.h"

char *itos(char *buf, uint16_t val, uint8_t dig, char pad) {
  char *str = buf;
  str += dig;
  for (; dig > 0; dig--) {
    str--;
    *str = (val == 0) ? pad : "0123456789"[val % 10];
    val /= 10;
  }
  return str;
}
