#ifndef _24LC64_H_
#define _24LC64_H_

#include <xc.h>

#include "i2c.h"

// 24LC64 I2C Address
#define 24LC64_I2C_ADDR 0x50 << 1
// 24LC64 CAPACITY
#define 24LC64_ADDR_MAX 0xffff
// 24LC64 Data Width
#define 24LC64_DATA_MAX 0xff

extern void 24lc64_i2c_write(uint16_t addr, uint8_t data);
extern void 24lc64_i2c_read(uint16_t addr, uint8_t* data);

#endif
