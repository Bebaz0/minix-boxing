#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "config.h"

typedef enum {
    ANIM_IDLE,
    ANIM_SPECIAL,
    ANIM_PUNCH,
    ANIM_DEFENSE,
    ANIM_WIN,
    ANIM_LOSE
} AnimState;

typedef struct {
    int       hp;
    int       combo;
    AnimState anim;
    int       anim_frame;       // 0 or 1
    int       anim_timer_ms;    // counts up
    int       tooltip_type;
    int       tooltip_timer_ms;
    int       tooltip_x;
    int       tooltip_y;
} Player;

/**
 * @brief Initializes a player to full HP, empty combo and idle animation.
 *
 * @param p Player to initialize
 */
void player_init(Player *p);

/**
 * @brief Resets the per-round player state (combo, animation and tooltip).
 *
 * Unlike player_init(), HP is left untouched so it persists across the round.
 *
 * @param p Player to reset
 */
void player_reset_round_state(Player *p);

/**
 * @brief Applies damage to a player, clamping HP to a minimum of 0.
 *
 * @param p Player taking damage
 * @param dmg Amount of HP to subtract
 */
void player_take_damage(Player *p, int dmg);

/**
 * @brief Increases the player's combo meter, clamped to PLAYER_MAX_COMBO.
 *
 * @param p Player to update
 * @param pts Combo points to add
 */
void player_add_combo(Player *p, int pts);

/**
 * @brief Clears the player's combo meter back to zero.
 *
 * @param p Player to update
 */
void player_reset_combo(Player *p);

/**
 * @brief Checks whether the player has been knocked out.
 *
 * @param p Player to query
 * @return true if HP is 0 or below, false otherwise
 */
bool player_is_dead(const Player *p);

/**
 * @brief Checks whether the player's combo meter is full.
 *
 * @param p Player to query
 * @return true if the combo is at PLAYER_MAX_COMBO, false otherwise
 */
bool player_combo_full(const Player *p);

#endif /* PLAYER_H */
