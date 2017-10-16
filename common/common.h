#ifndef COMMON_H
#define COMMON_H

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#include "i2c.h"
#include "spi.h"
#include "st7032i.h"
#include "adt7410.h"
#include "eeprom.h"
#include "uart.h"
#include "utils.h"

/* System Clock */
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#endif	/* COMMON_H */
