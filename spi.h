#ifndef SPI_H
#define SPI_H

extern void spi_start(void);
extern void spi_stop(void);
extern void spi_write(unsigned char data);
extern uint8_t spi_read(void);
extern uint8_t spi_read16(void);

#endif /* SPI_H */
