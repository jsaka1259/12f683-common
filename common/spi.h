#ifndef _SPI_H_
#define _SPI_H_

#include <xc.h>
#include <stdint.h>

#define CS  GP5
#define SCK GP2
#define SO  GP4
#define SI  GP3

extern void spi_start(void);
extern void spi_stop(void);
extern void spi_write(uint8_t data);
extern uint8_t spi_read(void);
extern uint8_t spi_read16(void);

#endif
