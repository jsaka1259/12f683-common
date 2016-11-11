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
void rs_getc(uint8_t* code)
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
        *code = dat;            // Return Valid Data
    }
    else
    {
        *code = 0xFF;           // Return Error Flag
    }
}

/* Send String */
void rs_puts(uint8_t *buf)
{
    while(*buf)
    {
        rs_putc(*buf++);
    }
}

/* Receive String */
void rs_gets(uint8_t* buf)
{
    uint8_t ch;
    uint8_t i = 0;
    
    while(1)
    {
        rs_getc(&ch);
        if((ch == 0x0A) || (ch == 0x0D))
        {
            buf[i] = 0x00;
            rs_crlf();
            break;
        }
        else if((i > 0) && (ch == 0x08))
        {
            rs_puts("\b \b");
            i--;
        }
        else if((ch >= 0x20) && (ch <= 0x7E))
        {
            buf[i++] = (uint8_t)ch;
            rs_putc(ch);
        }
        else
        {
            rs_putc(0x07);
        }
    }
}

/* Send CRLF */
void rs_crlf(void)
{
    rs_puts("\r\n");
}
