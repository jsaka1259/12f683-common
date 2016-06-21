#ifndef LCD_H
#define	LCD_H

#define ST7032_ADRES    0x7c    // LCD Address
#define CONTRAST        0x60    // CONTRAST

extern void lcd_init(void);
extern void lcd_cmd(uint8_t);
extern void lcd_putch(uint8_t);
extern void lcd_puts(const uint8_t *);
extern void lcd_clear(void);
extern void delay_100ms(uint16_t);

#endif	/* LCD_H */

