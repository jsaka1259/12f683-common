#ifndef LCD_H
#define	LCD_H

void lcd_init(void);
void lcd_clear(void);
void lcd_cmd(uint8_t cmd);
void lcd_putc(uint8_t data);
void lcd_puts(const uint8_t *buf);
void delay_100ms(uint16_t time);

#endif	/* LCD_H */

