#ifndef I2C_H
#define I2C_H

extern void i2c_start(void);
extern void i2c_stop(void);
extern uint8_t i2c_write(uint8_t data);
extern uint8_t i2c_read(uint8_t ack);

#endif /* I2C_H */

