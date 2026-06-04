#include "pause_view.h"
#include "active_view.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"
#include "sprites.h"
#include "../assets/pause_rectangle.xpm"

#define TEXT_WHITE  0xFFFFu
#define TEXT_YELLOW 0xFFE0u

#define POPUP_W      620
#define POPUP_H      401
#define POPUP_X      ((SCREEN_WIDTH  - POPUP_W) / 2)
#define POPUP_Y      ((SCREEN_HEIGHT - POPUP_H) / 2)

#define PAUSE_TITLE_Y    (POPUP_Y + 82)
#define PAUSE_RESUME_Y   (POPUP_Y + 175)
#define PAUSE_EXIT_Y     (POPUP_Y + 245)

static sprite_t *get_pause_panel(void) {
    static sprite_t *panel = NULL;

    if (panel == NULL)
        panel = sprite_create((xpm_map_t)pause_rectangle_xpm);

    return panel;
}

static font_t *get_pause_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 3);
    }

    return font;
}

static void draw_pause_button(const Game *g, font_t *font, int option_idx,
                              const char *label, uint16_t y) {
    uint32_t color = (g->pause_selected == option_idx) ? TEXT_YELLOW : TEXT_WHITE;
    uint16_t text_width = font_string_width(font, label);

    font_draw_string_color(font, label, (SCREEN_WIDTH - text_width) / 2, y, color);
}

void pause_view_draw(const Game *g) {
    active_view_draw(g);

    font_t *font = get_pause_font();
    sprite_t *panel = get_pause_panel();

    if (panel != NULL)
        sprite_draw(panel, POPUP_X, POPUP_Y);

    if (font == NULL)
        return;

    uint16_t title_w = font_string_width(font, "PAUSED");
    font_draw_string_color(font, "PAUSED", (SCREEN_WIDTH - title_w) / 2, PAUSE_TITLE_Y, TEXT_YELLOW);

    draw_pause_button(g, font, 0, "RESUME", PAUSE_RESUME_Y);
    draw_pause_button(g, font, 1, "EXIT",   PAUSE_EXIT_Y);
}
