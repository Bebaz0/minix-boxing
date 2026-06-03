#include <string.h>
#include "game.h"
#include "combat.h"

#define ANIM_FRAME_DURATION_MS 50

static void tick_anim(Player *p, int delta_ms) {
    p->anim_timer_ms += delta_ms;
    if (p->anim_timer_ms >= ANIM_FRAME_DURATION_MS) {
        p->anim_timer_ms -= ANIM_FRAME_DURATION_MS;
        p->anim_frame = (p->anim_frame + 1) % FIGHTER_IDLE_FRAME_COUNT;
    }
}

void game_init(Game *g) {
    memset(g, 0, sizeof(*g));
    g->state = GS_MENU;
    player_init(&g->p1);
    player_init(&g->p2);
    menu_init(&g->menu);
    char_select_init(&g->char_select);
    g->response_window_ms = INITIAL_RESPONSE_WINDOW_MS;
    g->round_duration_ms = ROUND_DURATION_MS;
    g->round_number = 1;
}

void game_update(Game *g, int delta_ms) {
    if (g->state != GS_ACTIVE)
        return;

    tick_anim(&g->p1, delta_ms);
    tick_anim(&g->p2, delta_ms);
}

void game_handle_key(Game *g, char key) {
    /*TODO*/
}

void game_handle_click(Game *g, int mx, int my, MouseButton button) {
    /*TODO*/
    (void)button;
   
}

bool game_is_over(const Game *g) {
    return g->state == GS_GAME_OVER;
}
