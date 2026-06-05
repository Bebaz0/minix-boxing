#include "game_over_view.h"
#include "active_view.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"
#include "sprites.h"
#include "../../assets/ui/pause_rectangle.xpm"

#define TEXT_WHITE  0xFFFFu
#define TEXT_YELLOW 0xFFE0u
#define TEXT_BLUE   0x001Fu
#define TEXT_RED    0xF800u

#define POPUP_W      620
#define POPUP_H      401
#define POPUP_X      ((SCREEN_WIDTH  - POPUP_W) / 2)
#define POPUP_Y      ((SCREEN_HEIGHT - POPUP_H) / 2)

/* Normal (no record) layout */
#define END_TITLE_Y   (POPUP_Y + 82)
#define END_RESTART_Y (POPUP_Y + 175)
#define END_MENU_Y    (POPUP_Y + 245)

/* Record layout — title shifts up, name-input section in the middle */
#define REC_TITLE_Y   (POPUP_Y + 38)
#define REC_BADGE_Y   (POPUP_Y + 100)
#define REC_PROMPT_Y  (POPUP_Y + 140)
#define REC_INPUT_Y   (POPUP_Y + 175)
#define REC_RESTART_Y (POPUP_Y + 255)
#define REC_MENU_Y    (POPUP_Y + 323)

#define CURSOR_W 12
#define CURSOR_H 24

static sprite_t *get_end_panel(void) {
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

static void draw_end_button(font_t *font, int option_idx, int selected,
                            const char *label, uint16_t y) {
    uint32_t color = (selected == option_idx) ? TEXT_YELLOW : TEXT_WHITE;
    uint16_t w = font_string_width(font, label);
    font_draw_string_color(font, label, (SCREEN_WIDTH - w) / 2, y, color);
}

void game_over_view_draw(const Game *g) {
    static int blink_counter = 0;
    blink_counter++;

    active_view_draw(g);

    font_t *title_font = get_title_font();
    font_t *body_font  = get_body_font();
    sprite_t *panel    = get_end_panel();

    if (panel != NULL)
        sprite_draw(panel, POPUP_X, POPUP_Y);

    if (title_font == NULL)
        return;

    const char *winner_text;
    uint32_t winner_color;
    if (g->winner == 1) {
        winner_text  = "PLAYER 1 WINS!";
        winner_color = TEXT_BLUE;
    } else if (g->winner == 2) {
        winner_text  = "PLAYER 2 WINS!";
        winner_color = TEXT_RED;
    } else {
        winner_text  = "DRAW!";
        winner_color = TEXT_WHITE;
    }

    if (g->is_new_record >= 1) {
        const char *primary_label = (g->winner == 0) ? "NEXT ROUND" : "PLAY AGAIN";

        draw_centered(title_font, winner_text, REC_TITLE_Y, winner_color);

        if (body_font != NULL) {
            draw_centered(body_font, "NEW RECORD!", REC_BADGE_Y, TEXT_YELLOW);
            draw_centered(body_font, "INSERT YOUR NAME:", REC_PROMPT_Y, TEXT_YELLOW);

            uint16_t name_w = font_string_width(body_font, g->name_input);
            uint16_t name_x = (SCREEN_WIDTH - name_w - CURSOR_W - 4) / 2;
            font_draw_string_color(body_font, g->name_input, name_x, REC_INPUT_Y, TEXT_WHITE);

            if (g->is_new_record == 1 && (blink_counter / 15) % 2 == 0) {
                uint16_t cx = (uint16_t)(name_x + name_w + 4);
                view_draw_rect(cx, REC_INPUT_Y, CURSOR_W, CURSOR_H, TEXT_WHITE);
            }
        }

        int sel = (g->is_new_record == 1) ? -1 : g->round_end_selected;
        draw_end_button(title_font, 0, sel, primary_label, REC_RESTART_Y);
        draw_end_button(title_font, 1, sel, "BACK TO MENU", REC_MENU_Y);
    } else {
        const char *primary_label = (g->winner == 0) ? "NEXT ROUND" : "PLAY AGAIN";

        draw_centered(title_font, winner_text, END_TITLE_Y, winner_color);
        draw_end_button(title_font, 0, g->round_end_selected, primary_label, END_RESTART_Y);
        draw_end_button(title_font, 1, g->round_end_selected, "BACK TO MENU", END_MENU_Y);
    }
}
