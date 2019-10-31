#ifndef _UART_H_
#define _UART_H_

#include <xc.h>
#include <stdint.h>

// Detect Delay Time
#define DTIME 10

// Baudrate
#define BAUDRATE 9600
#define BAUD     (uint8_t)(((_XTAL_FREQ / BAUDRATE) / 16) - 1)

#define TXPIN GP4
#define RXPIN GP5

extern void uart_init(void);
extern void uart_putc(uint8_t code);
extern void uart_puts(uint8_t *buf);
extern uint8_t uart_getc(void);

#endif
