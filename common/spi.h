#ifndef SPI_H
#define SPI_H

extern void spi_start(void);
extern void spi_end(void);
extern void spi_out(unsigned char data);
extern unsigned char spi_rcv(void);
extern unsigned int spi_rcv16(void);

#endif	/* SPI_H */