#ifndef ANIMATION_H
#define ANIMATION_H

#include "player.h"

/**
 * @brief Maps a character-selection index to its fighter type.
 *
 * @param char_idx Character slot index
 * @return Fighter type associated with the character
 */
int animation_fighter_for_character(int char_idx);

/**
 * @brief Advances a player's sprite animation by one tick.
 *
 * Accumulates elapsed time and, once a frame's duration passes, advances the
 * current animation. One-shot animations (punch/special/defense) return to idle
 * when finished; the idle animation loops.
 *
 * @param p Player whose animation is updated
 * @param fighter_type Fighter type, used to look up per-fighter frame counts
 * @param delta_ms Elapsed time since the last tick, in milliseconds
 */
void animation_tick_player(Player *p, int fighter_type, int delta_ms);

#endif /* ANIMATION_H */
