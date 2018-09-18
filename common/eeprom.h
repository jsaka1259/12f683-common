#ifndef EEPROM_H
#define EEPROM_H

extern void eeprom_i2c_write(uint16_t, uint8_t);
extern void eeprom_i2c_read(uint16_t, uint8_t*);

#endif /* EEPROM_H */
