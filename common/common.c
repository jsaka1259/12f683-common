#include <common.h>

// CONFIG
#pragma config FOSC  = INTOSCIO // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE  = OFF      // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select bit (MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP    = OFF      // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD   = OFF      // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO  = OFF      // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

void common_init(void)
{
    OSCCON = 0x70;              // OSC 8MHz
    GPIO   = 0x00;              // GPIO default Low
    TRISIO = 0x28;              // GP3, 5 Input Mode
    ANSEL  = 0x00;              // Set All Digital Pin
    CMCON0 = 0x07;              // Comparator OFF
    WPU    = 0x00;              // Assign GPIO to Pull-Up Resistor
    nGPPU  = 1;                 // InValid Pull-Up Resistor
    
    lcd_init();
    rs232c_ini();
    
    PEIE = 1;
    GIE  = 1;
    
    __delay_us(500);
}
