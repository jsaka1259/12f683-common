#include "utils.h"

char *itos(char *buf, int32_t val, uint8_t radix, int8_t dig, char pad) {
  uint8_t minus = 0;

  if (radix != 2 && radix != 8 && radix != 10 && radix != 16)
    radix = 10;

  if (radix == 10) {
    minus = val & 0x8000 ? 1 : 0;
    val = minus ? -val : val;
  }

  buf[dig] = 0;
  buf += dig;

  for (; dig > 0; dig--) {
    buf--;
    *buf = RADIX_NUMBER_STR[val % radix];
    val /= radix;
    if (!val)
      break;
  }

  for (dig--; dig > 0; dig--) {
    buf--;
    if (minus) {
      minus = 0;
      *buf = '-';
    } else
      *buf = pad;
  }
  return buf;
}

char *utos(char *buf, uint32_t val, uint8_t radix, int8_t dig, char pad) {
  buf[dig] = 0;
  buf += dig;

  if (radix != 2 && radix != 8 && radix != 10 && radix != 16)
    radix = 10;

  for (; dig > 0; dig--) {
    buf--;
    *buf = RADIX_NUMBER_STR[val % radix];
    val /= radix;
    if (!val)
      break;
  }

  for (dig--; dig > 0; dig--) {
    buf--;
    *buf = pad;
  }

  return buf;
}

uint32_t get_frac_part(int16_t val, uint8_t accu, uint8_t dig) {
  uint32_t frac = 0;
  uint32_t n = 1;
  int8_t i;

  accu = accu & 0x0f;
  dig = dig < 10 ? dig : 9;
  while (dig--)
    n *= 10;

  for (i = accu - 1; i >= 0; i--)
    frac += (n / (1 << (accu - i))) * ((val & (1 << i)) >> i);

  return frac;
}
