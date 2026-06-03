#include "game_over_view.h"
#include "active_view.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"

#define END_BOX_COLOR     0x7BEFu  /* mid grey outline */
#define END_BG_COLOR      0x0000u  /* black popup fill */
#define END_BTN_COLOR     0xC618u
#define END_BTN_SEL_COLOR 0xFFE0u

#define POPUP_W      500
#define POPUP_H      250
#define POPUP_X      ((SCREEN_WIDTH  - POPUP_W) / 2)   /* 262 */
#define POPUP_Y      ((SCREEN_HEIGHT - POPUP_H) / 2)   /* 259 */
#define POPUP_BORDER 4

#define END_BTN_W     440
#define END_BTN_H     56
#define END_BTN_X     ((SCREEN_WIDTH - END_BTN_W) / 2) /* 292 */
#define END_TITLE_Y   (POPUP_Y + 24)                   /* 283 */
#define END_RESTART_Y (POPUP_Y + 96)                   /* 355 */
#define END_MENU_Y    (POPUP_Y + 168)                  /* 427 */

static font_t *get_end_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 3);
    }

    return font;
}

static void draw_end_text(font_t *font, const char *text, uint16_t x, uint16_t y) {
    if (font != NULL)
        font_draw_string(font, text, x, y);
}

static void draw_centered_end_text(font_t *font, const char *text, uint16_t y) {
    uint16_t width = font_string_width(font, text);
    draw_end_text(font, text, (SCREEN_WIDTH - width) / 2, y);
}

static void draw_end_button(const Game *g, font_t *font, int option_idx,
                            const char *label, uint16_t y) {
    uint32_t color = (g->round_end_selected == option_idx)
                     ? END_BTN_SEL_COLOR : END_BTN_COLOR;
    uint16_t text_width = font_string_width(font, label);

    view_draw_rect(END_BTN_X, y, END_BTN_W, END_BTN_H, color);
    draw_end_text(font,
                  label,
                  END_BTN_X + (END_BTN_W - text_width) / 2,
                  y + (END_BTN_H - font_line_height(font)) / 2);
}

void game_over_view_draw(const Game *g) {
    active_view_draw(g);

    font_t *font = get_end_font();

    view_draw_rect(POPUP_X, POPUP_Y, POPUP_W, POPUP_H, END_BOX_COLOR);
    view_draw_rect(POPUP_X + POPUP_BORDER, POPUP_Y + POPUP_BORDER,
                   POPUP_W - 2 * POPUP_BORDER, POPUP_H - 2 * POPUP_BORDER,
                   END_BG_COLOR);

    if (font == NULL)
        return;

    const char *title;
    if      (g->winner == 1) title = "PLAYER 1 WINS!";
    else if (g->winner == 2) title = "PLAYER 2 WINS!";
    else                     title = "DRAW!";

    draw_centered_end_text(font, title, END_TITLE_Y);
    draw_end_button(g, font, 0, "RESTART ROUND", END_RESTART_Y);
    draw_end_button(g, font, 1, "MENU", END_MENU_Y);
}
