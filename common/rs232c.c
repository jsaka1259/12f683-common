#include <common.h>

static volatile uint8_t dat;
static volatile uint8_t bCnt;
static volatile uint8_t bPos;

/* Initialize RS232C */
void rs232c_ini(void)
{
    T2CON  = 0x01;              // 1/4 Pre, 1/1 Post
    TMR2IF = 0;                 // Clear Interrupt Flag
    TXPIN = 1;
}

/* Send 1 Byte */
void rs_putc(uint8_t code)
{
    dat  = code;                // Set Send Data
    bCnt = 0;                   // Initialize Bit Counter
    bPos = 0x01;                // Initialize Bit Position
    PR2  = BAUD;                // Set Baudrate
    
    TXPIN = 0;                  // Output START Bit
    TMR2  = 0;                  // Initialize TMR2
    T2CON = 0x05;               // 1/4 Pre, 1/1 Post
    while(bCnt < 10)            // Wait Send Complate
    {
        while(!TMR2IF);         // Wait Detect TMR2 Flag
        TMR2IF = 0;
        bCnt++;
        if(bCnt > 0 && bCnt < 9)    // 1-8bit
        {
            TXPIN = (dat & bPos)? 1: 0;     // Output Data Bit
            bPos <<= 1;         // Bit Shift
        }
        if(bCnt == 9)           // End Data
        {
            TXPIN = 1;          // Output STOP Bit
        }
        if(bCnt == 10)          // End STOP Bit
        {
            T2CON = 0x01;       // Stop TMR2
        }
    }
}

/* Receive 1 Byte */
uint8_t rs_getc(void)
{
    while(RXPIN);               // Waite START Bit
    bCnt = 0;                   // Initialize Bit Counter
    dat  = 0;                   // Clear Receive Data
    bPos = 0x01;                // Initialize Bit Position
    TMR2 = 0;                   // Initialize TMR2
    PR2  = DTIME;               // Set 1/2 Bit Width
    
    TMR2IF = 0;                 // Defeat TMR2 Interrupt Flag
    T2CON  = 0x05;              // 1/4 Pre, 1/1 Post
    
    while(bCnt < 10)            // Wait Receive Complate
    {
        while(!TMR2IF)          // Wait TMR2 Interrupt
            ;
        TMR2IF = 0;
        switch(bCnt)
        {
            case 0:             // Process START Bit
                if(RXPIN)
                {
                    bCnt = 0xFF;
                }
                else
                {
                    PR2 = BAUD;
                    bCnt++;
                }
                break;
            case 9:             // Process STOP Bit
                if(RXPIN)
                {
                    bCnt++;
                }
                else
                {
                    bCnt = 0xFF;
                }
                T2CON = 0x01;   // Stop TMR2
                break;
            default:            // Process 1-8bit Data
                if(RXPIN)
                {
                    dat |= bPos;
                }
                bPos <<= 1;
                bCnt++;
        }
    }
    
    if(bCnt == 10)
    {
        return(dat);            // Return Valid Data
    }
    else
    {
        return(0xFF);           // Return Error Flag
    }
}

/* Send String */
void rs_puts(uint8_t *buff)
{
    while(*buff)
    {
        rs_putc(*buff++);
    }
}

/* Receive String */
void rs_gets(uint8_t *buff)
{
    uint8_t *p, chr;
    
    p = buff;
    while(1)
    {
        chr = rs_getc();
        if(chr == 0xFF)
        {
            buff[0] = 'E';
            buff[1] = 'R';
            buff[2] = 'R';
            buff[3] = 0x00;
            break;
        }
        if(chr != 0x0d && chr != 0x0a)
        {
            *p++ = chr;
        }
        if(chr == 0x0d)
        {
            *p = 0x00;
        }
        if(chr == 0x0a)
        {
            *p = 0x00;
            break;
        }
    }
}

/* Send CRLF */
void rs_crlf(void)
{
    rs_puts("\r\n");
}
