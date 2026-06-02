#include "menu_view.h"
#include "font.h"
#include "sprites.h"
#include "config.h"
#include "view_utils.h"
#include "../assets/logo_menu.xpm"

#define MENU_BUTTON_COLOR   0xC618u
#define MENU_SELECTED_COLOR 0xFFE0u
#define LOGO_Y              40u

static font_t *get_menu_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 3);
    }

    return font;
}

static sprite_t *get_logo_sprite(void) {
    static sprite_t *logo_sprite = NULL;

    if (logo_sprite == NULL)
        logo_sprite = sprite_create(logo_menu);

    return logo_sprite;
}

static void draw_menu_text(font_t *font, const char *text, uint16_t x, uint16_t y) {
    if (font != NULL)
        font_draw_string(font, text, x, y);
}

static void draw_menu_button(const Game *g, font_t *font, MenuOption option, const char *label, uint16_t y) {
    uint32_t color = g->menu.selected == option ? MENU_SELECTED_COLOR : MENU_BUTTON_COLOR;
    uint16_t text_width = font_string_width(font, label);

    view_draw_rect(MENU_BUTTON_X, y, MENU_BUTTON_W, MENU_BUTTON_H, color);
    draw_menu_text(font,
                   label,
                   MENU_BUTTON_X + (MENU_BUTTON_W - text_width) / 2,
                   y + (MENU_BUTTON_H - font_line_height(font)) / 2);
}

void menu_view_draw(const Game *g) {
    font_t *font = get_menu_font();
    sprite_t *logo = get_logo_sprite();

    view_draw_background();
    if (logo != NULL)
        sprite_draw(logo, (SCREEN_WIDTH - logo->width) / 2, LOGO_Y);

    draw_menu_button(g, font, MENU_OPTION_START, "START", MENU_START_Y);
    draw_menu_button(g, font, MENU_OPTION_EXIT, "EXIT", MENU_EXIT_Y);
}
