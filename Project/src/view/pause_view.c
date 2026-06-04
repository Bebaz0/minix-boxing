#include "pause_view.h"
#include "active_view.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"

#define PAUSE_BOX_COLOR     0x7BEFu
#define PAUSE_BG_COLOR      0x0000u
#define PAUSE_BTN_COLOR     0xC618u
#define PAUSE_BTN_SEL_COLOR 0xFFE0u

#define POPUP_W      500
#define POPUP_H      250
#define POPUP_X      ((SCREEN_WIDTH  - POPUP_W) / 2)
#define POPUP_Y      ((SCREEN_HEIGHT - POPUP_H) / 2)
#define POPUP_BORDER 4

#define PAUSE_BTN_W      440
#define PAUSE_BTN_H      56
#define PAUSE_BTN_X      ((SCREEN_WIDTH - PAUSE_BTN_W) / 2)
#define PAUSE_TITLE_Y    (POPUP_Y + 24)
#define PAUSE_RESUME_Y   (POPUP_Y + 96)
#define PAUSE_EXIT_Y     (POPUP_Y + 168)

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
    uint32_t color = (g->pause_selected == option_idx)
                     ? PAUSE_BTN_SEL_COLOR : PAUSE_BTN_COLOR;
    uint16_t text_width = font_string_width(font, label);

    view_draw_rect(PAUSE_BTN_X, y, PAUSE_BTN_W, PAUSE_BTN_H, color);
    font_draw_string(font,
                     label,
                     PAUSE_BTN_X + (PAUSE_BTN_W - text_width) / 2,
                     y + (PAUSE_BTN_H - font_line_height(font)) / 2);
}

void pause_view_draw(const Game *g) {
    active_view_draw(g);

    font_t *font = get_pause_font();

    view_draw_rect(POPUP_X, POPUP_Y, POPUP_W, POPUP_H, PAUSE_BOX_COLOR);
    view_draw_rect(POPUP_X + POPUP_BORDER, POPUP_Y + POPUP_BORDER,
                   POPUP_W - 2 * POPUP_BORDER, POPUP_H - 2 * POPUP_BORDER,
                   PAUSE_BG_COLOR);

    if (font == NULL)
        return;

    uint16_t title_w = font_string_width(font, "PAUSE");
    font_draw_string(font, "PAUSE", (SCREEN_WIDTH - title_w) / 2, PAUSE_TITLE_Y);

    draw_pause_button(g, font, 0, "RESUME", PAUSE_RESUME_Y);
    draw_pause_button(g, font, 1, "EXIT",   PAUSE_EXIT_Y);
}
