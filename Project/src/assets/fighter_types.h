#ifndef FIGHTER_TYPES_H
#define FIGHTER_TYPES_H

#include "config.h"

#define FIGHTER_W              192
#define FIGHTER_H_PX           383

#define FIGHTER_TYPE_DEFAULT     0
#define FIGHTER_TYPE_GOKU        1
#define FIGHTER_TYPE_VEGETA      2
#define FIGHTER_TYPE_EMPTY     (-1)
#define FIGHTER_TYPE_COUNT       3


static const int char_fighter_type[CHAR_COUNT] = {
    FIGHTER_TYPE_DEFAULT, 
    FIGHTER_TYPE_GOKU,    
    FIGHTER_TYPE_VEGETA,  
    FIGHTER_TYPE_EMPTY,   
    FIGHTER_TYPE_EMPTY    
};

static inline int char_get_fighter_type(int char_idx) {
    if (char_idx < 0 || char_idx >= CHAR_COUNT) return FIGHTER_TYPE_DEFAULT;
    int t = char_fighter_type[char_idx];
    return (t == FIGHTER_TYPE_EMPTY) ? FIGHTER_TYPE_DEFAULT : t;
}

static inline int char_has_sprite(int char_idx) {
    if (char_idx < 0 || char_idx >= CHAR_COUNT) return 0;
    return char_fighter_type[char_idx] != FIGHTER_TYPE_EMPTY;
}

#endif
