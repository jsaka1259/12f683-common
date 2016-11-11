#include <common.h>

uint8_t* common_format(uint8_t* buf, const uint8_t* fmt, ...)
{
    va_list arg;
    
    va_start(arg, fmt);
    vsprintf(buf, fmt, arg);
    va_end(arg);
    
    return buf;
}

uint32_t strtoh(uint8_t* buf)
{
    uint32_t hex  = 0x00000000;
    uint8_t  temp = 0x00;
    uint8_t  lc   = 0;
    
    while(buf[lc] != 0x00)
    {
        if(isdigit(buf[lc]))
        {
            temp = buf[lc] - 0x30; 
        }
        else if(isxdigit(buf[lc]))
        {
            buf[lc] = toupper(buf[lc]);
            temp = buf[lc] - 0x41 + 0x0A;
        }
        else
        {
            rs_puts("strtoh : Error\n");
            return 0xFFFFFFFF;
        }
        hex = hex * 16 + temp;
        lc++;
    }
    return hex;
}
