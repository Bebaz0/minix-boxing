#include <string.h>
#include "game.h"
#include "combat.h"

#define ANIM_FRAME_DURATION_MS 60

static void tick_anim(Player *p, int delta_ms) {
    p->anim_timer_ms += delta_ms;
    if (p->anim_timer_ms >= ANIM_FRAME_DURATION_MS) {
        p->anim_timer_ms -= ANIM_FRAME_DURATION_MS;
        p->anim_frame ^= 1;  // flip between 0 and 1
    }
}

void game_init(Game *g) {
    memset(g, 0, sizeof(*g));
    g->state = GS_ACTIVE;
}

void game_update(Game *g, int delta_ms) {
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
    /* TODO: Devolver true se g->state == GS_GAME_OVER. */
    (void)g;
    return false;
}
