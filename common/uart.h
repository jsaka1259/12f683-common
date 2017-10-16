#ifndef UART_H
#define	UART_H

void uart_init(void);
void uart_putc(uint8_t code);
void uart_puts(uint8_t*);
uint8_t uart_getc(void);

#endif	/* UART_H */
