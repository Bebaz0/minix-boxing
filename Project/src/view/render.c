#include "render.h"
#include "active_view.h"
#include "menu_view.h"
#include "round_start_view.h"
#include "game_over_view.h"
#include "pause_view.h"
#include "leaderboard_view.h"
#include "char_select_view.h"
#include "instructions_view.h"
#include "view_utils.h"
#include "video.h"
#include "sprites.h"
#include "../assets/ui/cursor.xpm"

static sprite_t *get_cursor_sprite(void) {
    static sprite_t *cursor = NULL;

    if (cursor == NULL)
        cursor = sprite_create((xpm_map_t)cursor_xpm);

    return cursor;
}

static void draw_cursor(const Game *g) {
    sprite_t *cursor = get_cursor_sprite();

    if (cursor != NULL)
        sprite_draw(cursor, (uint16_t)g->mouse_x, (uint16_t)g->mouse_y);
}

static void render_menu_frame(const Game *g, bool force_full_redraw) {
    static bool menu_frame_valid = false;
    static MenuOption previous_selected = MENU_OPTION_COUNT;
    static bool previous_hint_visible = true;
    static int previous_mouse_x = 0;
    static int previous_mouse_y = 0;
    bool hint_visible = menu_view_hint_visible(g);

    sprite_t *cursor = get_cursor_sprite();
    uint16_t cursor_w = cursor != NULL ? cursor->width : 12;
    uint16_t cursor_h = cursor != NULL ? cursor->height : 16;

    if (force_full_redraw || !menu_frame_valid ||
        previous_selected != g->menu.selected ||
        previous_hint_visible != hint_visible) {
        menu_view_draw(g);
    } else {
        menu_view_restore_region(g, previous_mouse_x, previous_mouse_y, cursor_w, cursor_h);
    }

    draw_cursor(g);
    previous_mouse_x = g->mouse_x;
    previous_mouse_y = g->mouse_y;
    previous_selected = g->menu.selected;
    previous_hint_visible = hint_visible;
    menu_frame_valid = true;
}

static int round_start_phase(const Game *g) {
    if (g->state_timer_ms <= ROUND_SPLASH_MS)
        return 0;

    int digit = ((g->state_timer_ms - ROUND_SPLASH_MS) + 999) / 1000;
    if (digit < 1) digit = 1;
    if (digit > 3) digit = 3;
    return digit;
}

static void render_round_start_frame(const Game *g, bool force_full_redraw) {
    static int previous_phase = -1;
    int phase = round_start_phase(g);

    if (force_full_redraw || previous_phase != phase) {
        round_start_view_draw(g);
        vg_flip();
        previous_phase = phase;
    }
}

void render_frame(const Game *g) {
    static GameState previous_state = GS_QUIT;

    switch (g->state) {
        case GS_ACTIVE:
            active_view_draw(g);
            break;

        case GS_MENU:
            render_menu_frame(g, previous_state != GS_MENU);
            previous_state = g->state;
            vg_flip();
            return;

        case GS_ROUND_END:
            game_over_view_draw(g);
            break;

        case GS_ROUND_START:
            render_round_start_frame(g, previous_state != GS_ROUND_START);
            previous_state = g->state;
            return;

        case GS_PAUSE:
            pause_view_draw(g);
            break;

        case GS_LEADERBOARD:
            leaderboard_view_draw(g);
            break;

        case GS_CHAR_SELECT:
            char_select_view_draw(g);
            break;

        case GS_INSTRUCTIONS:
            instructions_view_draw(g);
            break;

        case GS_QUIT:
            return;
            break;
    }

    previous_state = g->state;
    draw_cursor(g);
    vg_flip();
}
