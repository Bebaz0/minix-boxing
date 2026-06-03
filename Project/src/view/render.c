#include "render.h"
#include "active_view.h"
#include "menu_view.h"
#include "round_start_view.h"
#include "game_over_view.h"
#include "pause_view.h"
#include "view_utils.h"
#include "video.h"

void render_frame(const Game *g) {
    switch (g->state) {
        case GS_ACTIVE:
            active_view_draw(g);
            break;

        case GS_MENU:
            menu_view_draw(g);
            break;

        case GS_ROUND_END:
            game_over_view_draw(g);
            break;

        case GS_ROUND_START:
            round_start_view_draw(g);
            break;

        case GS_PAUSE:
            pause_view_draw(g);
            break;

        case GS_QUIT:
            view_draw_background(BG_COLOR);
            break;
    }

    vg_flip();
}
