#ifndef LCD_H
#define LCD_H

extern void lcd_init(void);
extern void lcd_clear(void);
extern void lcd_cmd(uint8_t cmd);
extern void lcd_putc(uint8_t data);
extern void lcd_puts(const uint8_t *buf);
extern void delay_100ms(uint16_t time);

#endif /* LCD_H */

