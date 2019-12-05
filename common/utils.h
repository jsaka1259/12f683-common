#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>

#define RADIX_NUMBER_STR "0123456789ABCDEF"

extern char *itos(char *buf, int32_t val, uint8_t radix, int8_t dig, char pad);
extern char *utos(char *buf, uint32_t val, uint8_t radix, int8_t dig, char pad);
extern uint32_t get_frac_part(int16_t val, uint8_t accu, uint8_t dig);

#endif
