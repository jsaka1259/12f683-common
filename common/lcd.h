#ifndef LCD_H
#define	LCD_H

#define CONTRAST 0x60           // CONTRAST

extern void lcd_init(void);
extern void lcd_cmd(uint8_t);
extern void lcd_putc(uint8_t);
extern void lcd_puts(const uint8_t *);
extern void lcd_clear(void);
extern void delay_100ms(uint16_t);

#endif	/* LCD_H */

