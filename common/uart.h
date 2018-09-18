#ifndef UART_H
#define UART_H

extern void uart_init(void);
extern void uart_putc(uint8_t code);
extern void uart_puts(uint8_t*);
extern uint8_t uart_getc(void);

#endif /* UART_H */
