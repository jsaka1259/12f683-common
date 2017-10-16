#ifndef SPI_H
#define SPI_H

void spi_start(void);
void spi_end(void);
void spi_out(unsigned char data);
uint8_t spi_rcv(void);
uint8_t spi_rcv16(void);

#endif	/* SPI_H */