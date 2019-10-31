#ifndef _I2C_H_
#define _I2C_H_

#include <xc.h>
#include <stdint.h>

#define SDA     GP5
#define SCL     GP4
#define TRISSDA TRISIO5

extern void i2c_start(void);
extern void i2c_stop(void);
extern uint8_t i2c_write(uint8_t data);
extern uint8_t i2c_read(uint8_t ack);

#endif

