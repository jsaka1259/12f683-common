#include "common.h"

void spi_start(void) {
  CS = 0;
}

void spi_stop(void) {
  CS = 1;
}

void spi_write(uint8_t data) {
  uint8_t i;
  uint8_t bit_pos = 0x80;

  for(i = 0; i < 8; i++) {
    if((data & bit_pos) != 0)
      SO = 1;
    else
      SO = 0;

    bit_pos = bit_pos >> 1;
    SCK = 1;
    SCK = 1;
    SCK = 0;
  }
}

uint8_t spi_read(void) {
  uint8_t i;
  uint8_t bit_pos = 0x80;
  uint8_t data = 0;

  for(i = 0; i < 8; i++) {
    SCK = 1;

    if(SI)
      data |= bit_pos;

    bit_pos = bit_pos >> 1;
    SCK = 0;
  }
  return (data);
}

uint16_t spi_rcv16(void) {
  uint8_t  i;
  uint16_t bit_pos = 0x8000;
  uint16_t data = 0;

  for(i = 0; i < 16; i++) {
    SCK = 1;

    if(SI)
      data |= bit_pos;

    bit_pos = bit_pos >> 1;
    SCK = 0;
  }
  return (data);
}
