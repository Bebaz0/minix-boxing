#ifndef FIGHTER_TYPES_H
#define FIGHTER_TYPES_H

#include "config.h"

#define FIGHTER_W              192
#define FIGHTER_H_PX           383

/* Tamanho pequeno (Mario e Sonic). */
#define SMALL_FIGHTER_W         80
#define SMALL_FIGHTER_H        152

#define FIGHTER_TYPE_DEFAULT     0
#define FIGHTER_TYPE_GOKU        1
#define FIGHTER_TYPE_VEGETA      2
#define FIGHTER_TYPE_MARIO       3
#define FIGHTER_TYPE_SONIC       4
#define FIGHTER_TYPE_COUNT       5

static const int char_fighter_type[CHAR_COUNT] = {
    FIGHTER_TYPE_DEFAULT,
    FIGHTER_TYPE_GOKU,
    FIGHTER_TYPE_VEGETA,
    FIGHTER_TYPE_MARIO,
    FIGHTER_TYPE_SONIC
};

static inline int char_get_fighter_type(int char_idx) {
    if (char_idx < 0 || char_idx >= CHAR_COUNT) return FIGHTER_TYPE_DEFAULT;
    return char_fighter_type[char_idx];
}

static inline int fighter_w(int fighter_type) {
    return (fighter_type == FIGHTER_TYPE_MARIO || fighter_type == FIGHTER_TYPE_SONIC)
           ? SMALL_FIGHTER_W : FIGHTER_W;
}

static inline int fighter_h(int fighter_type) {
    return (fighter_type == FIGHTER_TYPE_MARIO || fighter_type == FIGHTER_TYPE_SONIC)
           ? SMALL_FIGHTER_H : FIGHTER_H_PX;
}

static inline int fighter_get_special_frame_count(int fighter_type) {
    switch (fighter_type) {
        case FIGHTER_TYPE_DEFAULT: return 5;
        case FIGHTER_TYPE_GOKU:   return 4;
        case FIGHTER_TYPE_VEGETA: return 5;
        case FIGHTER_TYPE_MARIO:  return 9;
        case FIGHTER_TYPE_SONIC:  return 9;
        default:                  return 0;
    }
}

static inline int fighter_get_punch_frame_count(int fighter_type) {
    switch (fighter_type) {
        case FIGHTER_TYPE_DEFAULT: return 4;
        case FIGHTER_TYPE_GOKU:   return 4;
        case FIGHTER_TYPE_VEGETA: return 3;
        case FIGHTER_TYPE_MARIO:  return 3;
        case FIGHTER_TYPE_SONIC:  return 2;
        default:                  return 0;
    }
}

static inline int fighter_get_defense_frame_count(int fighter_type) {
    switch (fighter_type) {
        case FIGHTER_TYPE_DEFAULT: return 2;
        case FIGHTER_TYPE_GOKU:   return 2;
        case FIGHTER_TYPE_VEGETA: return 2;
        case FIGHTER_TYPE_MARIO:  return 2;
        case FIGHTER_TYPE_SONIC:  return 2;
        default:                  return 0;
    }
}

static inline int fighter_get_idle_frame_count(int fighter_type) {
    switch (fighter_type) {
        case FIGHTER_TYPE_DEFAULT: return 4;
        case FIGHTER_TYPE_GOKU:   return 6;
        case FIGHTER_TYPE_VEGETA: return 6;
        case FIGHTER_TYPE_MARIO:  return 3;
        case FIGHTER_TYPE_SONIC:  return 7;
        default:                  return 4;
    }
}

#endif /* FIGHTER_TYPES_H */
