#include "bitwise.h"
#include <stdarg.h>

#define TODO return 255

uint8_t clear(uint8_t msk, int pos) { 
    return msk & ~(1 << pos); 
}

uint8_t set(uint8_t msk, int pos) { 
    return msk | (1 << pos); 
}

bool is_set(uint8_t msk, int pos) { 
    return msk & (1 << pos); 
}

uint8_t lsb(uint16_t wide_msk) { 
    return wide_msk & 0xFF;
}

uint8_t msb(uint16_t wide_msk) { 
    return (wide_msk & 0xFF00) >> 8;
}

uint8_t mask(int pos, ...) { 
    uint8_t res = 0x00;
    va_list args;
    va_start(args, pos);

    while (pos != MSK_END){
        res |= (1 << pos);
        pos = va_arg(args, int);
    }

    va_end(args);

    return res;
}
