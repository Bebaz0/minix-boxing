#include "fighter_sprites.h"
#include "../assets/fighter.h"  

static sprite_t *idle_cache[FIGHTER_TYPE_COUNT][FIGHTER_IDLE_FRAME_COUNT];

sprite_t *fighter_get_idle_sprite(int fighter_type, int frame_index) {
    if (fighter_type < 0 || fighter_type >= FIGHTER_TYPE_COUNT)
        fighter_type = FIGHTER_TYPE_DEFAULT;
    if (frame_index < 0 || frame_index >= FIGHTER_IDLE_FRAME_COUNT)
        frame_index = 0;

    if (idle_cache[fighter_type][frame_index] == NULL)
        idle_cache[fighter_type][frame_index] =
            sprite_create(fighter_get_idle_xpm(fighter_type, frame_index));

    return idle_cache[fighter_type][frame_index];
}
