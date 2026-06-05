#include "fighter_sprites.h"
#include "../assets/fighter.h"

#define FIGHTER_MAX_SPECIAL_FRAMES 9
#define FIGHTER_MAX_PUNCH_FRAMES   4
#define FIGHTER_MAX_DEFENSE_FRAMES 2

static sprite_t *idle_cache[FIGHTER_TYPE_COUNT][FIGHTER_IDLE_FRAME_COUNT];
static sprite_t *special_cache[FIGHTER_TYPE_COUNT][FIGHTER_MAX_SPECIAL_FRAMES];
static sprite_t *punch_cache[FIGHTER_TYPE_COUNT][FIGHTER_MAX_PUNCH_FRAMES];
static sprite_t *defense_cache[FIGHTER_TYPE_COUNT][FIGHTER_MAX_DEFENSE_FRAMES];

sprite_t *fighter_get_idle_sprite(int fighter_type, int frame_index) {
    if (fighter_type < 0 || fighter_type >= FIGHTER_TYPE_COUNT)
        fighter_type = FIGHTER_TYPE_DEFAULT;
    if (frame_index < 0 || frame_index >= fighter_get_idle_frame_count(fighter_type))
        frame_index = 0;

    if (idle_cache[fighter_type][frame_index] == NULL)
        idle_cache[fighter_type][frame_index] =
            sprite_create(fighter_get_idle_xpm(fighter_type, frame_index));

    return idle_cache[fighter_type][frame_index];
}

sprite_t *fighter_get_special_sprite(int fighter_type, int frame_index) {
    int count = fighter_get_special_frame_count(fighter_type);
    if (count == 0)
        return fighter_get_idle_sprite(fighter_type, frame_index);

    if (fighter_type < 0 || fighter_type >= FIGHTER_TYPE_COUNT)
        fighter_type = FIGHTER_TYPE_DEFAULT;
    if (frame_index < 0 || frame_index >= count)
        frame_index = 0;

    if (special_cache[fighter_type][frame_index] == NULL)
        special_cache[fighter_type][frame_index] =
            sprite_create(fighter_get_special_xpm(fighter_type, frame_index));

    return special_cache[fighter_type][frame_index];
}

sprite_t *fighter_get_punch_sprite(int fighter_type, int frame_index) {
    int count = fighter_get_punch_frame_count(fighter_type);
    if (count == 0)
        return fighter_get_idle_sprite(fighter_type, frame_index);

    if (fighter_type < 0 || fighter_type >= FIGHTER_TYPE_COUNT)
        fighter_type = FIGHTER_TYPE_DEFAULT;
    if (frame_index < 0 || frame_index >= count)
        frame_index = 0;

    if (punch_cache[fighter_type][frame_index] == NULL)
        punch_cache[fighter_type][frame_index] =
            sprite_create(fighter_get_punch_xpm(fighter_type, frame_index));

    return punch_cache[fighter_type][frame_index];
}

sprite_t *fighter_get_defense_sprite(int fighter_type, int frame_index) {
    int count = fighter_get_defense_frame_count(fighter_type);
    if (count == 0)
        return fighter_get_idle_sprite(fighter_type, frame_index);

    if (fighter_type < 0 || fighter_type >= FIGHTER_TYPE_COUNT)
        fighter_type = FIGHTER_TYPE_DEFAULT;

    if (frame_index < 0 || frame_index >= count)
        frame_index = 0;

    if (defense_cache[fighter_type][frame_index] == NULL)
        defense_cache[fighter_type][frame_index] =
            sprite_create(fighter_get_defense_xpm(fighter_type, frame_index));

    return defense_cache[fighter_type][frame_index];
}
