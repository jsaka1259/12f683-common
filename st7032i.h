#ifndef ST7032I_H
#define ST7032I_H

extern void st7032i_init(void);
extern void st7032i_clear(void);
extern void st7032i_cmd(uint8_t cmd);
extern void st7032i_putc(uint8_t data);
extern void st7032i_puts(const uint8_t *buf);
extern void delay_100ms(uint16_t time);

#endif /* ST7032I_H */

