#include "name_input_view.h"
#include "active_view.h"
#include "font.h"
#include "view_utils.h"
#include "config.h"
#include "sprites.h"
#include "../assets/pause_rectangle.xpm"

#define TEXT_WHITE  0xFFFFu
#define TEXT_YELLOW 0xFFE0u

#define POPUP_W  620
#define POPUP_H  401
#define POPUP_X  ((SCREEN_WIDTH  - POPUP_W) / 2)
#define POPUP_Y  ((SCREEN_HEIGHT - POPUP_H) / 2)

#define TITLE_Y       (POPUP_Y + 60)
#define PROMPT_Y      (POPUP_Y + 150)
#define INPUT_Y       (POPUP_Y + 205)
#define CONFIRM_Y     (POPUP_Y + 295)
#define SKIP_Y        (POPUP_Y + 335)

#define CURSOR_W  12
#define CURSOR_H  32

static sprite_t *get_panel(void) {
    static sprite_t *panel = NULL;
    if (panel == NULL)
        panel = sprite_create((xpm_map_t)pause_rectangle_xpm);
    return panel;
}

static font_t *get_title_font(void) {
    static font_t *font = NULL;
    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 3);
    }
    return font;
}

static font_t *get_body_font(void) {
    static font_t *font = NULL;
    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 2);
    }
    return font;
}

static void draw_centered(font_t *font, const char *text, uint16_t y, uint32_t color) {
    uint16_t w = font_string_width(font, text);
    font_draw_string_color(font, text, (SCREEN_WIDTH - w) / 2, y, color);
}

void name_input_view_draw(const Game *g) {
    static int blink_counter = 0;
    blink_counter++;

    active_view_draw(g);

    sprite_t *panel = get_panel();
    if (panel != NULL)
        sprite_draw(panel, POPUP_X, POPUP_Y);

    font_t *title_font = get_title_font();
    font_t *body_font  = get_body_font();

    if (title_font != NULL)
        draw_centered(title_font, "NEW RECORD", TITLE_Y, TEXT_YELLOW);

    if (body_font == NULL)
        return;

    draw_centered(body_font, "Enter your name:", PROMPT_Y, TEXT_WHITE);

    uint16_t name_w = font_string_width(body_font, g->name_input);
    uint16_t name_x = (SCREEN_WIDTH - name_w - CURSOR_W - 4) / 2;

    font_draw_string_color(body_font, g->name_input, name_x, INPUT_Y, TEXT_WHITE);

    /* blinking cursor: ~1 Hz at 30 fps */
    if ((blink_counter / 15) % 2 == 0) {
        uint16_t cx = (uint16_t)(name_x + name_w + 4);
        view_draw_rect(cx, INPUT_Y, CURSOR_W, CURSOR_H, TEXT_WHITE);
    }

    draw_centered(body_font, "ENTER to confirm", CONFIRM_Y, TEXT_WHITE);
    draw_centered(body_font, "ESC to skip", SKIP_Y, TEXT_WHITE);
}
