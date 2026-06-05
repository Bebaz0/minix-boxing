#ifndef FIGHTER_SPRITES_H
#define FIGHTER_SPRITES_H

#include "sprites.h"
#include "../../assets/fighters/fighter_types.h"

/**
 * @brief Returns a fighter's idle-animation frame, decoding and caching it.
 *
 * @param fighter_type Fighter type identifier
 * @param frame_index Frame index within the idle animation
 * @return Cached sprite for the frame, or NULL on failure
 */
sprite_t *fighter_get_idle_sprite(int fighter_type, int frame_index);

/**
 * @brief Returns a fighter's special-move frame, decoding and caching it.
 *
 * @param fighter_type Fighter type identifier
 * @param frame_index Frame index within the special animation
 * @return Cached sprite for the frame, or NULL on failure
 */
sprite_t *fighter_get_special_sprite(int fighter_type, int frame_index);

/**
 * @brief Returns a fighter's punch frame, decoding and caching it.
 *
 * @param fighter_type Fighter type identifier
 * @param frame_index Frame index within the punch animation
 * @return Cached sprite for the frame, or NULL on failure
 */
sprite_t *fighter_get_punch_sprite(int fighter_type, int frame_index);

/**
 * @brief Returns a fighter's defense frame, decoding and caching it.
 *
 * @param fighter_type Fighter type identifier
 * @param frame_index Frame index within the defense animation
 * @return Cached sprite for the frame, or NULL on failure
 */
sprite_t *fighter_get_defense_sprite(int fighter_type, int frame_index);

#endif /* FIGHTER_SPRITES_H */
