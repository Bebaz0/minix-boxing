#include "game_over_view.h"
#include "active_view.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"
#include "sprites.h"
#include "../assets/pause_rectangle.xpm"

#define TEXT_WHITE  0xFFFFu
#define TEXT_YELLOW 0xFFE0u
#define TEXT_BLUE   0x001Fu
#define TEXT_RED    0xF800u

#define POPUP_W      620
#define POPUP_H      401
#define POPUP_X      ((SCREEN_WIDTH  - POPUP_W) / 2)
#define POPUP_Y      ((SCREEN_HEIGHT - POPUP_H) / 2)

#define END_TITLE_Y   (POPUP_Y + 82)
#define END_RESTART_Y (POPUP_Y + 175)
#define END_MENU_Y    (POPUP_Y + 245)

static sprite_t *get_end_panel(void) {
    static sprite_t *panel = NULL;

    if (panel == NULL)
        panel = sprite_create((xpm_map_t)pause_rectangle_xpm);

    return panel;
}

static font_t *get_end_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 3);
    }

    return font;
}

static void draw_end_text(font_t *font, const char *text, uint16_t x, uint16_t y, uint32_t color) {
    if (font != NULL)
        font_draw_string_color(font, text, x, y, color);
}

static void draw_centered_end_text(font_t *font, const char *text, uint16_t y, uint32_t color) {
    uint16_t width = font_string_width(font, text);
    draw_end_text(font, text, (SCREEN_WIDTH - width) / 2, y, color);
}

static void draw_end_button(const Game *g, font_t *font, int option_idx,
                            const char *label, uint16_t y) {
    uint32_t color = (g->round_end_selected == option_idx) ? TEXT_YELLOW : TEXT_WHITE;
    uint16_t text_width = font_string_width(font, label);

    draw_end_text(font, label, (SCREEN_WIDTH - text_width) / 2, y, color);
}

void game_over_view_draw(const Game *g) {
    active_view_draw(g);

    font_t *font = get_end_font();
    sprite_t *panel = get_end_panel();

    if (panel != NULL)
        sprite_draw(panel, POPUP_X, POPUP_Y);

    if (font == NULL)
        return;

    const char *title;
    uint32_t title_color;
    if (g->winner == 1) {
        title = "PLAYER 1 WINS!";
        title_color = TEXT_BLUE;
    }
    else if (g->winner == 2) {
        title = "PLAYER 2 WINS!";
        title_color = TEXT_RED;
    }
    else {
        title = "DRAW!";
        title_color = TEXT_WHITE;
    }

    draw_centered_end_text(font, title, END_TITLE_Y, title_color);
    draw_end_button(g, font, 0, "RESTART ROUND", END_RESTART_Y);
    draw_end_button(g, font, 1, "MENU", END_MENU_Y);
}
