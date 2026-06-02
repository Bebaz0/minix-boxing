#include "render.h"
#include "menu_view.h"
#include "active_view.h"
#include "view_utils.h"
#include "game.h"
#include "video.h"

void render_frame(const Game *g) {
    switch (g->state) {
        case GS_ACTIVE:
        case GS_ROUND_END:
            active_view_draw(g);
            break;

        case GS_MENU:
            menu_view_draw(g);
            break;

        case GS_PAUSE:
        case GS_ROUND_START:
        case GS_GAME_OVER:
            view_draw_background();
            break;
    }
    vg_flip();
}
