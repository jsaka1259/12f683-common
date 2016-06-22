/* 
 * File:   i2c.h
 * Author: sakaguchi
 *
 * Created on 2016/04/04, 17:39
 */

#ifndef I2C_H
#define	I2C_H

extern void i2c_start(void);
extern void i2c_stop(void);
extern uint8_t i2c_write(uint8_t);
extern uint8_t i2c_read(uint8_t);

#endif	/* I2C_H */

