#include <common.h>

/* ST7032I */
#define ST7032I_I2C_ADDR 0x7C           // ST7032I I2C Address
#define ST7032I_CONTRAST 0x18           // for 5V
//#define ST7032I_CONTRAST 0x30           // for 3.3V

void st7032i_init(void)
{
    delay_100ms(1);
    st7032i_cmd(0x38);                  // 8bit 2line Noraml mode
    st7032i_cmd(0x39);                  // 8bit 2line Extend mode
    st7032i_cmd(0x14);                  // OSC 183Hz BIAS 1/5
    st7032i_cmd(0x70 + (ST7032I_CONTRAST & 0x0F)); // CONTRAST
    st7032i_cmd(0x5C + (ST7032I_CONTRAST >> 4));   // CONTRAST
    st7032i_cmd(0x6A);                  // Follower for 5V
//  st7032i_cmd(0x6B);                  // Follower for 3.3V
    delay_100ms(3);
    st7032i_cmd(0x38);                  // Set Normal mode
    st7032i_cmd(0x0C);                  // Display On
    st7032i_cmd(0x01);                  // Clear Display
}

void st7032i_cmd(uint8_t cmd)
{
    i2c_start();                        // I2C Start Condition
    i2c_write(ST7032I_I2C_ADDR);        // ST7032I Device Address
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

void st7032i_putc(uint8_t data)
{    
    i2c_start();                        // I2C Start Condition
    i2c_write(ST7032I_I2C_ADDR);        // ST7032I Device Address
    i2c_write(0x40);                    // Set Data Mode
    i2c_write(data);                    // Output Data
    i2c_stop();                         // I2C Stop Condition
    __delay_us(30);                     // Wait 30usec
}

void st7032i_puts(const uint8_t* buf)
{
    uint8_t i = 0;
    
    while(buf[i] != 0x00)
    {
        st7032i_putc(buf[i++]);
    }
}

void st7032i_clear(void)
{
    st7032i_cmd(0x01);                  // Clear Display
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
