#include "round_start_view.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"

static font_t *get_countdown_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(0);
        font_set_scale(font, 10);
    }

    return font;
}

void round_start_view_draw(const Game *g) {
    view_draw_background(BG_COLOR);

    font_t *font = get_countdown_font();
    if (font == NULL)
        return;

    int digit = (g->state_timer_ms + 999) / 1000;
    if (digit < 1) digit = 1;
    if (digit > 3) digit = 3;

    char str[2] = {'0' + digit, '\0'};

    uint16_t x = (SCREEN_WIDTH  - font_string_width(font, str)) / 2;
    uint16_t y = (SCREEN_HEIGHT - font_line_height(font))       / 2;

    font_draw_string(font, str, x, y);
}
