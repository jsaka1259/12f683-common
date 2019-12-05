#include "24lc64.h"

void 24lc64_i2c_write(uint16_t addr, uint8_t data) {
  i2c_start();
  i2c_write(24LC64_I2C_ADDR);
  i2c_write((uint8_t)addr >> 8);
  i2c_write((uint8_t)addr & 0xFF);
  i2c_write(data);
  i2c_stop();

  __delay_ms(20);
}

void 24lc64_i2c_read(uint16_t addr, uint8_t* data) {
  i2c_start();
  i2c_write(24LC64_I2C_ADDR);
  i2c_write((uint8_t)addr >> 8);
  i2c_write((uint8_t)addr & 0xFF);
  i2c_start();
  i2c_write(24LC64_I2C_ADDR | 1);
  *data = i2c_read(0);
  i2c_stop();

  __delay_us(30);
}
