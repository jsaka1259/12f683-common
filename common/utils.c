#include "utils.h"

uint16_t itostring(uint8_t digit, uint8_t* buf) {
    uint8_t i = digit;
    uint16_t data = 0;
    
    buf += digit;
    for(; i > 0; i--) {
        buf--;
        *buf = (data % 10) + '0';
        data = data / 10;
    }
    return data;
}
