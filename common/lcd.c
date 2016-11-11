#include <common.h>

static uint8_t lcd_line = 0x80;

void lcd_init(void)
{
    delay_100ms(1);
    lcd_cmd(0x38);                      // 8bit 2line Noraml mode
    lcd_cmd(0x39);                      // 8bit 2line Extend mode
    lcd_cmd(0x14);                      // OSC 183Hz BIAS 1/5
    lcd_cmd(0x70 + (CONTRAST & 0x0F));  // CONTRAST
    lcd_cmd(0x50 + (CONTRAST >> 4));    // CONTRAST
    lcd_cmd(0x6A);                      // Follower for 5V
    delay_100ms(3);
    lcd_cmd(0x38);                      // Set Normal mode
    lcd_cmd(0x0C);                      // Display On
    lcd_cmd(0x01);                      // Clear Display
}

void lcd_cmd(uint8_t cmd)
{
    i2c_start();                        // I2C Start Condition
    i2c_write(LCD_I2C_ADDR);            // LCD Device Address
    i2c_write(0x00);                    // Set Command Mode
    i2c_write(cmd);                     // Output Command
    i2c_stop();                         // I2C Stop Condition
    
    /* Clear or Home */
    if((cmd == 0x01) || (cmd == 0x02))
    {
        __delay_us(2);                  // Wait 2usec
    }
    else
    {
        __delay_us(30);                 // Wait 30usec
    }
}

void lcd_putc(uint8_t data)
{    
    i2c_start();                        // I2C Start Condition
    i2c_write(LCD_I2C_ADDR);            // LCD Device Address
    i2c_write(0x40);                    // Set Data Mode
    i2c_write(data);                    // Output Data
    i2c_stop();                         // I2C Stop Condition
    __delay_us(30);                     // Wait 30usec
}

void lcd_puts(const uint8_t* buf)
{
    uint8_t i = 0;
    
    lcd_cmd(lcd_line);
    while(buf[i] != 0x00)
    {
        if(i >= LCD_MAX_COLUMN)
        {
            break;
        }
        lcd_putc(buf[i++]);
    }
}

void lcd_crlf(void)
{
    if(lcd_line == 0x80)
    {
        lcd_line = 0xC0;
    }
    else
    {
        lcd_line = 0x80;
    }
    lcd_cmd(lcd_line);
}

void lcd_clear(void)
{
    lcd_cmd(0x01);                      // Clear Display
    lcd_line = 0x80;
}

void delay_100ms(uint16_t time)
{
    time *= 4;                          // 4 times
    while(time)
    {
        __delay_ms(25);                 // 25msec
        time--;                         // 100msec X time
    }
}
