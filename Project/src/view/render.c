#include "render.h"
#include "sprites.h"
#include "game.h"
#include "config.h"
#include "video.h"
#include "../assets/fighter.h"

/* Dark-grey arena background in RGB565 */
#define BG_COLOR   0x9904u

/* Fighter vertical baseline (pixels from top of screen) */
#define FIGHTER_Y  300u

/* Horizontal inset from screen edges */
#define FIGHTER_INSET 100u

static void draw_background(void) {
    for (uint16_t row = 0; row < SCREEN_HEIGHT; row++)
        vg_draw_hline(0, row, SCREEN_WIDTH, BG_COLOR);
}
static const char **get_idle_frame(int frame_index) {
    return frame_index == 0 ? fighter_idle0_xpm : fighter_idle1_xpm;
}

void render_frame(const Game *g) {
    switch (g->state) {
        case GS_ACTIVE:
            draw_background();
            draw_sprite(get_idle_frame(g->p1.anim_frame), FIGHTER_INSET, FIGHTER_Y);
            draw_sprite_mirrored(get_idle_frame(g->p2.anim_frame),
                                SCREEN_WIDTH - FIGHTER_INSET - FIGHTER_W, FIGHTER_Y);
            break;
        case GS_MENU:
        case GS_ROUND_START:
        case GS_ROUND_END:
        case GS_GAME_OVER:
            draw_background();
            break;
    }
    vg_flip();
}
