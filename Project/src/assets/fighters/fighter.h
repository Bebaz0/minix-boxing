#ifndef FIGHTER_H
#define FIGHTER_H

#include "fighter_types.h"
#include <lcom/lcf.h>

/* ── Default ────────────────────────────────────────────────────── */
#include "default/fighter_idle0.xpm"
#include "default/fighter_idle1.xpm"
#include "default/fighter_idle2.xpm"
#include "default/fighter_idle3.xpm"
#include "default/fighter_idle4.xpm"

static const char * const *default_idle_frames[5] = {
    fighter_idle0_xpm,
    fighter_idle1_xpm,
    fighter_idle2_xpm,
    fighter_idle3_xpm,
    fighter_idle4_xpm
};

/* ── Goku ───────────────────────────────────────────────────────── */
#include "goku/goku_idle0.xpm"
#include "goku/goku_idle1.xpm"
#include "goku/goku_idle2.xpm"
#include "goku/goku_idle3.xpm"
#include "goku/goku_idle4.xpm"
#include "goku/goku_idle5.xpm"

static const char * const *goku_idle_frames[6] = {
    (const char * const *)goku_idle0,
    (const char * const *)goku_idle1,
    (const char * const *)goku_idle2,
    (const char * const *)goku_idle3,
    (const char * const *)goku_idle4,
    (const char * const *)goku_idle5
};

/* ── Vegeta ─────────────────────────────────────────────────────── */
#include "vegeta/vegeta_idle0.xpm"
#include "vegeta/vegeta_idle1.xpm"
#include "vegeta/vegeta_idle2.xpm"
#include "vegeta/vegeta_idle3.xpm"
#include "vegeta/vegeta_idle4.xpm"
#include "vegeta/vegeta_idle5.xpm"

static const char * const *vegeta_idle_frames[6] = {
    (const char * const *)vegeta_idle0,
    (const char * const *)vegeta_idle1,
    (const char * const *)vegeta_idle2,
    (const char * const *)vegeta_idle3,
    (const char * const *)vegeta_idle4,
    (const char * const *)vegeta_idle5
};

/* ── Mario ──────────────────────────────────────────────────────── */
#include "mario/mario_idle_1.xpm"
#include "mario/mario_idle_2.xpm"
#include "mario/mario_idle_3.xpm"

static const char * const *mario_idle_frames[3] = {
    (const char * const *)mario_idle_1,
    (const char * const *)mario_idle_2,
    (const char * const *)mario_idle_3
};

/* ── Sonic ──────────────────────────────────────────────────────── */
#include "sonic/sonic_idle1.xpm"
#include "sonic/sonic_idle2.xpm"
#include "sonic/sonic_idle3.xpm"
#include "sonic/sonic_idle4.xpm"
#include "sonic/sonic_idle5.xpm"
#include "sonic/sonic_idle6.xpm"
#include "sonic/sonic_idle7.xpm"

static const char * const *sonic_idle_frames[7] = {
    (const char * const *)sonic_idle1,
    (const char * const *)sonic_idle2,
    (const char * const *)sonic_idle3,
    (const char * const *)sonic_idle4,
    (const char * const *)sonic_idle5,
    (const char * const *)sonic_idle6,
    (const char * const *)sonic_idle7
};


/* ── Special attack frames ──────────────────────────────────────── */
#include "goku/goku_special0.xpm"
#include "goku/goku_special1.xpm"
#include "goku/goku_special2.xpm"
#include "goku/goku_special3.xpm"

static const char * const *goku_special_frames[4] = {
    (const char * const *)goku_special0,
    (const char * const *)goku_special1,
    (const char * const *)goku_special2,
    (const char * const *)goku_special3
};

#include "vegeta/vegeta_special0.xpm"
#include "vegeta/vegeta_special1.xpm"
#include "vegeta/vegeta_special2.xpm"
#include "vegeta/vegeta_special3.xpm"
#include "vegeta/vegeta_special4.xpm"

static const char * const *vegeta_special_frames[5] = {
    (const char * const *)vegeta_special0,
    (const char * const *)vegeta_special1,
    (const char * const *)vegeta_special2,
    (const char * const *)vegeta_special3,
    (const char * const *)vegeta_special4
};

#include "mario/mario_special_1.xpm"
#include "mario/mario_special_2.xpm"
#include "mario/mario_special_3.xpm"
#include "mario/mario_special_4.xpm"
#include "mario/mario_special_5.xpm"
#include "mario/mario_special_6.xpm"
#include "mario/mario_special_7.xpm"
#include "mario/mario_special_8.xpm"
#include "mario/mario_special_9.xpm"

static const char * const *mario_special_frames[9] = {
    (const char * const *)mario_special_1,
    (const char * const *)mario_special_2,
    (const char * const *)mario_special_3,
    (const char * const *)mario_special_4,
    (const char * const *)mario_special_5,
    (const char * const *)mario_special_6,
    (const char * const *)mario_special_7,
    (const char * const *)mario_special_8,
    (const char * const *)mario_special_9
};

#include "sonic/sonic_special1.xpm"
#include "sonic/sonic_special2.xpm"
#include "sonic/sonic_special3.xpm"
#include "sonic/sonic_special4.xpm"
#include "sonic/sonic_special5.xpm"
#include "sonic/sonic_special6.xpm"
#include "sonic/sonic_special7.xpm"
#include "sonic/sonic_special8.xpm"
#include "sonic/sonic_special9.xpm"

static const char * const *sonic_special_frames[9] = {
    (const char * const *)sonic_special1,
    (const char * const *)sonic_special2,
    (const char * const *)sonic_special3,
    (const char * const *)sonic_special4,
    (const char * const *)sonic_special5,
    (const char * const *)sonic_special6,
    (const char * const *)sonic_special7,
    (const char * const *)sonic_special8,
    (const char * const *)sonic_special9
};

/**
 * @brief Returns the XPM data for a fighter's special-animation frame.
 *
 * @param fighter_type Fighter type identifier
 * @param frame_index Frame index within the special animation
 * @return XPM map for the frame, or NULL if the fighter has no special frames
 */
static inline const char * const *fighter_get_special_xpm(int fighter_type, int frame_index) {
    switch (fighter_type) {
        case FIGHTER_TYPE_GOKU:   return goku_special_frames[frame_index];
        case FIGHTER_TYPE_VEGETA: return vegeta_special_frames[frame_index];
        case FIGHTER_TYPE_MARIO:  return mario_special_frames[frame_index];
        case FIGHTER_TYPE_SONIC:  return sonic_special_frames[frame_index];
        default:                  return NULL;
    }
}

/* ── Punch frames ───────────────────────────────────────────────── */
#include "goku/goku_punch0.xpm"
#include "goku/goku_punch1.xpm"
#include "goku/goku_punch2.xpm"
#include "goku/goku_punch3.xpm"

static const char * const *goku_punch_frames[4] = {
    (const char * const *)goku_punch0,
    (const char * const *)goku_punch1,
    (const char * const *)goku_punch2,
    (const char * const *)goku_punch3
};

#include "vegeta/vegeta_punch0.xpm"
#include "vegeta/vegeta_punch1.xpm"
#include "vegeta/vegeta_punch2.xpm"

static const char * const *vegeta_punch_frames[3] = {
    (const char * const *)vegeta_punch0,
    (const char * const *)vegeta_punch1,
    (const char * const *)vegeta_punch2
};

#include "mario/mario_punch_1.xpm"
#include "mario/mario_punch_2.xpm"
#include "mario/mario_punch_3.xpm"

static const char * const *mario_punch_frames[3] = {
    (const char * const *)mario_punch_1,
    (const char * const *)mario_punch_2,
    (const char * const *)mario_punch_3
};

#include "sonic/sonic_punch1.xpm"
#include "sonic/sonic_punch2.xpm"

static const char * const *sonic_punch_frames[2] = {
    (const char * const *)sonic_punch1,
    (const char * const *)sonic_punch2
};

/**
 * @brief Returns the XPM data for a fighter's punch-animation frame.
 *
 * @param fighter_type Fighter type identifier
 * @param frame_index Frame index within the punch animation
 * @return XPM map for the frame, or NULL if the fighter has no punch frames
 */
static inline const char * const *fighter_get_punch_xpm(int fighter_type, int frame_index) {
    switch (fighter_type) {
        case FIGHTER_TYPE_GOKU:   return goku_punch_frames[frame_index];
        case FIGHTER_TYPE_VEGETA: return vegeta_punch_frames[frame_index];
        case FIGHTER_TYPE_MARIO:  return mario_punch_frames[frame_index];
        case FIGHTER_TYPE_SONIC:  return sonic_punch_frames[frame_index];
        default:                  return NULL;
    }
}

/* ── Defense frames ─────────────────────────────────────────────── */

#include "goku/goku_defense.xpm"

static const char * const *goku_defense_frames[2] = {
    (const char * const *)goku_defense,
    (const char * const *)goku_defense
};

#include "vegeta/vegeta_defense.xpm"

static const char * const *vegeta_defense_frames[2] = {
    (const char * const *)vegeta_defense,
    (const char * const *)vegeta_defense
};

#include "mario/mario_defense.xpm"

static const char * const *mario_defense_frames[2] = {
    (const char * const *)mario_defense,
    (const char * const *)mario_defense
};

/* Sonic defense reuses sonic_special6 (already included above) */

static const char * const *sonic_defense_frames[2] = {
    (const char * const *)sonic_special6,
    (const char * const *)sonic_special6
};

/**
 * @brief Returns the XPM data for a fighter's defense-animation frame.
 *
 * @param fighter_type Fighter type identifier
 * @param frame_index Frame index within the defense animation
 * @return XPM map for the frame, or NULL if the fighter has no defense frames
 */
static inline const char * const *fighter_get_defense_xpm(int fighter_type, int frame_index) {
    switch (fighter_type) {
        case FIGHTER_TYPE_GOKU:   return goku_defense_frames[frame_index];
        case FIGHTER_TYPE_VEGETA: return vegeta_defense_frames[frame_index];
        case FIGHTER_TYPE_MARIO:  return mario_defense_frames[frame_index];
        case FIGHTER_TYPE_SONIC:  return sonic_defense_frames[frame_index];
        default:                  return NULL;
    }
}

/**
 * @brief Returns the XPM data for a fighter's idle-animation frame.
 *
 * Out-of-range frame indices are clamped to frame 0.
 *
 * @param fighter_type Fighter type identifier
 * @param frame_index Frame index within the idle animation
 * @return XPM map for the frame
 */
static inline const char * const *fighter_get_idle_xpm(int fighter_type, int frame_index) {
    if (frame_index < 0 || frame_index >= fighter_get_idle_frame_count(fighter_type))
        frame_index = 0;
    switch (fighter_type) {
        case FIGHTER_TYPE_GOKU:   return goku_idle_frames[frame_index];
        case FIGHTER_TYPE_VEGETA: return vegeta_idle_frames[frame_index];
        case FIGHTER_TYPE_MARIO:  return mario_idle_frames[frame_index];
        case FIGHTER_TYPE_SONIC:  return sonic_idle_frames[frame_index];
        default:                  return default_idle_frames[frame_index];
    }
}

#endif /* FIGHTER_H */
