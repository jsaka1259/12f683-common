#include "utils.h"

void delay_100ms(uint16_t time) {
  time *= 4;

  while(time) {
    __delay_ms(25);
    time--;
  }
}
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
