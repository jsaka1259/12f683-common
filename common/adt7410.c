#include "adt7410.h"

void adt7410_init(uint8_t mode) {
  uint8_t mode_val;
  mode_val = 0x00 | 0x80;

  switch (mode) {
    case 0:
      mode_val = 0x00 | 0x80;
      break;
    case 1:
      mode_val = 0x40 | 0x80;
      break;
    case 2:
      mode_val = 0x60;
      break;
    default:
      break;
  }

  i2c_start();
  i2c_write(0x03);
  i2c_write(ADT7410_I2C_ADDR);
  i2c_write(mode_val);
  i2c_stop();
}

int16_t adt7410_read(uint8_t one_shot) {
  uint16_t val;

  if (one_shot == 1) {
    i2c_start();
    i2c_write(ADT7410_I2C_ADDR);
    i2c_write(0x03);
    i2c_write(0x20 | 0x80);
    i2c_stop();
    __delay_us(240);
  }

  i2c_start();
  i2c_write(0x00);
  i2c_write(0x01);
  i2c_start();
  i2c_write(ADT7410_I2C_ADDR | 1);
  val  = (uint16_t)i2c_read(0) << 8;
  val |= (uint16_t)i2c_read(0);
  i2c_stop();

  return (int16_t)val;
}
