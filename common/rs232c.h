#ifndef RS232C_H
#define	RS232C_H

#define DTIME       10      // Detect Delay Time

extern void rs232c_ini(void);
extern void rs_putc(uint8_t);
extern void rs_getc(uint8_t*);
extern void rs_gets(uint8_t*);
extern void rs_puts(uint8_t*);
extern void rs_crlf(void);

#endif	/* RS232C_H */
