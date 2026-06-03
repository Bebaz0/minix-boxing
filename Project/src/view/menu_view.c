#include "menu_view.h"
#include "font.h"
#include "sprites.h"
#include "config.h"
#include "view_utils.h"
#include "../assets/logo.xpm"
#include "../assets/menu_background.xpm"

#define MENU_BUTTON_COLOR   0x2104u
#define MENU_SELECTED_COLOR 0xD4A0u
#define LOGO_W              640u
#define LOGO_Y              60u
#define CURSOR_COLOR        0xFFFFu
#define CURSOR_SHADOW       0x0000u

static font_t *get_menu_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 3);
    }

    return font;
}

static sprite_t *get_logo_sprite(void) {
    static sprite_t *sprite = NULL;

    if (sprite == NULL)
        sprite = sprite_create(logo_xpm);

    return sprite;
}

static sprite_t *get_menu_background_sprite(void) {
    static sprite_t *sprite = NULL;

    if (sprite == NULL)
        sprite = sprite_create(menu_background_xpm);

    return sprite;
}

static void draw_menu_text(font_t *font, const char *text, uint16_t x, uint16_t y) {
    if (font != NULL)
        font_draw_string(font, text, x, y);
}

static void draw_menu_button(const Game *g, font_t *font, MenuOption option, const char *label, uint16_t y) {
    uint32_t color = g->menu.selected == option ? MENU_SELECTED_COLOR : MENU_BUTTON_COLOR;
    uint16_t text_width = font_string_width(font, label);

    view_draw_rect(MENU_BUTTON_X, y, MENU_BUTTON_W, MENU_BUTTON_H, color);
    view_draw_rect(MENU_BUTTON_X, y, MENU_BUTTON_W, 3, 0xFFFFu);
    view_draw_rect(MENU_BUTTON_X, y + MENU_BUTTON_H - 3, MENU_BUTTON_W, 3, 0x0000u);
    draw_menu_text(font,
                   label,
                   MENU_BUTTON_X + (MENU_BUTTON_W - text_width) / 2,
                   y + (MENU_BUTTON_H - font_line_height(font)) / 2);
}

static void draw_cursor_pixel(int x, int y, uint32_t color) {
    if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
        return;

    view_draw_rect((uint16_t)x, (uint16_t)y, 1, 1, color);
}

static void draw_mouse_cursor(int x, int y) {
    for (uint16_t i = 0; i < 16; i++) {
        for (uint16_t j = 0; j <= i; j++)
            draw_cursor_pixel(x + j, y + i, CURSOR_SHADOW);

        draw_cursor_pixel(x, y + i, CURSOR_COLOR);
        draw_cursor_pixel(x + i, y + i, CURSOR_COLOR);
    }

    for (uint16_t i = 0; i < 20; i++)
        draw_cursor_pixel(x, y + i, CURSOR_COLOR);

    for (uint16_t i = 0; i < 12; i++)
        draw_cursor_pixel(x + i, y, CURSOR_COLOR);
}

void menu_view_draw(const Game *g, int mouse_x, int mouse_y) {
    font_t *font = get_menu_font();

    sprite_draw(get_menu_background_sprite(), 0, 0);
    sprite_draw(get_logo_sprite(), (SCREEN_WIDTH - LOGO_W) / 2, LOGO_Y);
    draw_menu_button(g, font, MENU_OPTION_START, "START", MENU_START_Y);
    draw_menu_button(g, font, MENU_OPTION_EXIT, "EXIT", MENU_EXIT_Y);
    draw_mouse_cursor(mouse_x, mouse_y);
}
