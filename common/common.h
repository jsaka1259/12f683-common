#ifndef COMMON_H
#define	COMMON_H

#include <xc.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#include "i2c.h"
#include "lcd.h"
#include "rs232c.h"
#include "eeprom.h"

/* System Clock */
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

/* I2C */
#define SDA     GP1
#define SCL     GP0
#define TRISSDA TRISIO1

/* RS232C */
#define BAUDRATE 9600           // Baudrate
#define BAUD     ((_XTAL_FREQ/BAUDRATE)/16-1)
#define TXPIN    GP4
#define RXPIN    GP5

/* LCD */
#define LCD_I2C_ADDR   0x7C     // LCD I2C Address
#define LCD_MAX_LINE   2        // LCD Max Line
#define LCD_MAX_COLUMN 8        // LCD Max Column

/* EEPROM */
#define EEPROM_I2C_ADDR   0x50    // EEPROM I2C Address
#define EEPROM_ADDR_MAX   0xFFFF  // EEPROM CAPACITY
#define EEPROM_DATA_MAX   0xFF    // EEPROM Data Width

extern void common_init();
extern uint8_t* common_format(uint8_t*, const uint8_t*, ...);
extern uint32_t strtoh(uint8_t*);

#endif	/* COMMON_H */
