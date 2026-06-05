#ifndef FIGHTER_SPRITES_H
#define FIGHTER_SPRITES_H

#include "sprites.h"
#include "../../assets/fighters/fighter_types.h"

sprite_t *fighter_get_idle_sprite(int fighter_type, int frame_index);
sprite_t *fighter_get_special_sprite(int fighter_type, int frame_index);
sprite_t *fighter_get_punch_sprite(int fighter_type, int frame_index);
sprite_t *fighter_get_defense_sprite(int fighter_type, int frame_index);

#endif /* FIGHTER_SPRITES_H */
