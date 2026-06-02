#include "active_view.h"
#include "sprites.h"
#include "config.h"
#include "view_utils.h"
#include "../assets/fighter.h"

#define FIGHTER_Y     300u
#define FIGHTER_INSET 100u

static sprite_t *get_idle_frame(int frame_index) {
    static sprite_t *idle_sprites[FIGHTER_IDLE_FRAME_COUNT] = {0};

    if (frame_index < 0 || frame_index >= FIGHTER_IDLE_FRAME_COUNT)
        frame_index = 0;

    if (idle_sprites[frame_index] == NULL)
        idle_sprites[frame_index] = sprite_create(fighter_idle_frames[frame_index]);

    return idle_sprites[frame_index];
}

void active_view_draw(const Game *g) {
    view_draw_background();
    sprite_draw(get_idle_frame(g->p1.anim_frame), FIGHTER_INSET, FIGHTER_Y);
    sprite_draw_mirrored(get_idle_frame(g->p2.anim_frame),
                         SCREEN_WIDTH - FIGHTER_INSET - FIGHTER_W, FIGHTER_Y);
}
