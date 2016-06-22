#include <common.h>

void i2c_start(void)
{
    SDA = 0;                            // SDA Low
    TRISSDA = 0;                        // Set Output SDA
}

void i2c_stop(void)
{
    SCL = 0;                            // SCL Low
    __delay_us(1);
    SDA = 0;                            // SDA Low
    TRISSDA = 0;                        // Reset Output Mode
    SCL = 1;                            // Before SCL High
    __delay_us(1);
    SDA = 1;                            // After SDA High
    __delay_us(10);                     // Delay Interval
}

uint8_t i2c_write(uint8_t data)
{
    uint8_t i;
    uint8_t BitPos, ACK;
    
    /* Send Data */
    TRISSDA = 0;                        // Set Output Mode
    BitPos = 0x80;                      // Initialize Bit Position
    for(i = 0; i < 8; i++)              // Loop 8bit
    {
        SCL = 0;                        // SCL Low
        if((data & BitPos) != 0)        // Output Bit
        {
            SDA = 1;                    // SDA High
        }
        else
        {
            SDA = 0;                    // SDA Low
        }
        BitPos = BitPos >> 1;           // Move Bit Position
        SCL = 1;                        // Reset SCL High
    }
    
    /* Check ACK */
    SCL = 0;                            // SCL Low for One CLOCK
    TRISSDA = 1;                        // Set Input Mode
    __delay_us(2);
    SCL = 1;                            // Reset SCL High
    __delay_us(2);
    ACK = SDA;                          // Check ACK
    return ACK;                         // Return ACK
}

uint8_t i2c_read(uint8_t ack)
{
    uint8_t i;
    uint8_t BitPos, data;
    
    /* Recv Data */
    data = 0;
    BitPos = 0x80;                      // Initialize Bit Position
    for(i = 0; i < 8; i++)              // Loop 8bit
    {
        SCL = 0;                        // SCL Low
        TRISSDA = 1;                    // Set Input Mode
        __delay_us(3);                  // Ensure Pulse Width
        SCL = 1;                        // SCL High
        if(SDA)                         // Input Bit
        {
            data |= BitPos;
        }
        BitPos = BitPos >> 1;           // Shift Bit
    }
    
    /* Response ACK/NAK */
    SCL = 0;                            // SCL Low
    SDA = ack;                          // Output ACK or NAK
    TRISSDA = 0;                        // Set Output Mode
    __delay_us(2);                      // Ensure Pulse Width
    SCL = 1;                            // SCL High
    return data;                        // Return Data
}
