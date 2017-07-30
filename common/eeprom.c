#include <common.h>

/* EEPROM */
#define EEPROM_I2C_ADDR   0x50    // EEPROM I2C Address
#define EEPROM_ADDR_MAX   0xFFFF  // EEPROM CAPACITY
#define EEPROM_DATA_MAX   0xFF    // EEPROM Data Width

void eeprom_i2c_write(uint16_t addr, uint8_t data)
{
    i2c_start();
    i2c_write(EEPROM_I2C_ADDR << 1);
    i2c_write((uint8_t)addr >> 8);
    i2c_write((uint8_t)addr & 0xFF);
    i2c_write(data);
    i2c_stop();
    
    __delay_ms(20);
}

void eeprom_i2c_read(uint16_t addr, uint8_t* data)
{
    i2c_start();
    i2c_write(EEPROM_I2C_ADDR << 1);
    i2c_write((uint8_t)addr >> 8);
    i2c_write((uint8_t)addr & 0xFF);
    i2c_start();
    i2c_write((EEPROM_I2C_ADDR << 1) | 1);
    *data = i2c_read(0);
    i2c_stop();
    
    __delay_us(30);
}