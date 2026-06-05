#ifndef FIGHTER_H
#define FIGHTER_H

#include "fighter_types.h"
#include <lcom/lcf.h>

/* ── Default ────────────────────────────────────────────────────── */
#include "fighters/default/fighter_idle0.xpm"
#include "fighters/default/fighter_idle1.xpm"
#include "fighters/default/fighter_idle2.xpm"
#include "fighters/default/fighter_idle3.xpm"
#include "fighters/default/fighter_idle4.xpm"

static const char * const *default_idle_frames[FIGHTER_IDLE_FRAME_COUNT] = {
    fighter_idle0_xpm,
    fighter_idle1_xpm,
    fighter_idle2_xpm,
    fighter_idle3_xpm,
    fighter_idle4_xpm
};

/* ── Goku ───────────────────────────────────────────────────────── */
#include "fighters/goku/goku_idle0.xpm"
#include "fighters/goku/goku_idle1.xpm"
#include "fighters/goku/goku_idle2.xpm"
#include "fighters/goku/goku_idle3.xpm"
#include "fighters/goku/goku_idle4.xpm"

static const char * const *goku_idle_frames[FIGHTER_IDLE_FRAME_COUNT] = {
    (const char * const *)goku_idle0,
    (const char * const *)goku_idle1,
    (const char * const *)goku_idle2,
    (const char * const *)goku_idle3,
    (const char * const *)goku_idle4
};

/* ── Vegeta ─────────────────────────────────────────────────────── */
#include "fighters/vegeta/vegeta_idle0.xpm"
#include "fighters/vegeta/vegeta_idle1.xpm"
#include "fighters/vegeta/vegeta_idle2.xpm"
#include "fighters/vegeta/vegeta_idle3.xpm"
#include "fighters/vegeta/vegeta_idle4.xpm"

static const char * const *vegeta_idle_frames[FIGHTER_IDLE_FRAME_COUNT] = {
    (const char * const *)vegeta_idle0,
    (const char * const *)vegeta_idle1,
    (const char * const *)vegeta_idle2,
    (const char * const *)vegeta_idle3,
    (const char * const *)vegeta_idle4
};

static inline const char * const *fighter_get_idle_xpm(int fighter_type, int frame_index) {
    if (frame_index < 0 || frame_index >= FIGHTER_IDLE_FRAME_COUNT)
        frame_index = 0;
    switch (fighter_type) {
        case FIGHTER_TYPE_GOKU:   return goku_idle_frames[frame_index];
        case FIGHTER_TYPE_VEGETA: return vegeta_idle_frames[frame_index];
        default:                  return default_idle_frames[frame_index];
    }
}

#endif /* FIGHTER_H */
