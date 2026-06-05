#include "menu_view.h"
#include "sprites.h"
#include "config.h"
#include "font.h"
#include "../../assets/menu/menu_button_exit.xpm"
#include "../../assets/menu/menu_button_exit_selected.xpm"
#include "../../assets/menu/menu_button_instructions.xpm"
#include "../../assets/menu/menu_button_instructions_selected.xpm"
#include "../../assets/menu/menu_button_start.xpm"
#include "../../assets/menu/menu_button_start_selected.xpm"
#include "../../assets/backgrounds/menu_background.xpm"

#define MENU_HINT_TEXT  "PRESS L TO LEADERBOARD"
#define MENU_HINT_Y     690
#define MENU_HINT_COLOR 0xF800u
#define MENU_HINT_BLINK_MS 900

static sprite_t *get_menu_background_sprite(void) {
    static sprite_t *sprite = NULL;

    if (sprite == NULL)
        sprite = sprite_create(menu_background_xpm);

    return sprite;
}

static sprite_t *get_menu_button_sprite(MenuOption option, bool selected) {
    static sprite_t *sprites[MENU_OPTION_COUNT][2] = {{NULL}};
    xpm_map_t maps[MENU_OPTION_COUNT][2] = {
        {menu_button_start_xpm, menu_button_start_selected_xpm},
        {menu_button_instructions_xpm, menu_button_instructions_selected_xpm},
        {menu_button_exit_xpm, menu_button_exit_selected_xpm}
    };
    int selected_index = selected ? 1 : 0;

    if (option >= MENU_OPTION_COUNT)
        return NULL;

    if (sprites[option][selected_index] == NULL)
        sprites[option][selected_index] = sprite_create(maps[option][selected_index]);

    return sprites[option][selected_index];
}

static void draw_menu_button(const Game *g, MenuOption option, uint16_t y) {
    sprite_draw(get_menu_button_sprite(option, g->menu.selected == option), MENU_BUTTON_X, y);
}

static font_t *get_menu_hint_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(1);
        font_set_scale(font, 2);
    }

    return font;
}

static void draw_menu_hint(void) {
    font_t *font = get_menu_hint_font();
    if (font == NULL)
        return;

    uint16_t x = (SCREEN_WIDTH - font_string_width(font, MENU_HINT_TEXT)) / 2;
    font_draw_string_color(font, MENU_HINT_TEXT, x, MENU_HINT_Y, MENU_HINT_COLOR);
}

bool menu_view_hint_visible(const Game *g) {
    return (g->menu_blink_timer_ms / MENU_HINT_BLINK_MS) % 2 == 0;
}

static bool rects_intersect(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh) {
    return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
}

static void restore_button_if_needed(const Game *g, MenuOption option, uint16_t y,
                                     int x, int restore_y, uint16_t w, uint16_t h) {
    if (rects_intersect(x, restore_y, w, h, MENU_BUTTON_X, y, MENU_BUTTON_W, MENU_BUTTON_H))
        draw_menu_button(g, option, y);
}

void menu_view_draw(const Game *g) {
    sprite_draw(get_menu_background_sprite(), 0, 0);
    draw_menu_button(g, MENU_OPTION_START, MENU_START_Y);
    draw_menu_button(g, MENU_OPTION_INSTRUCTIONS, MENU_INSTRUCTIONS_Y);
    draw_menu_button(g, MENU_OPTION_EXIT, MENU_EXIT_Y);
    if (menu_view_hint_visible(g))
        draw_menu_hint();
}

void menu_view_restore_region(const Game *g, int x, int y, uint16_t w, uint16_t h) {
    sprite_draw_region(get_menu_background_sprite(), x, y, w, h, x, y);
    restore_button_if_needed(g, MENU_OPTION_START, MENU_START_Y, x, y, w, h);
    restore_button_if_needed(g, MENU_OPTION_INSTRUCTIONS, MENU_INSTRUCTIONS_Y, x, y, w, h);
    restore_button_if_needed(g, MENU_OPTION_EXIT, MENU_EXIT_Y, x, y, w, h);
    if (menu_view_hint_visible(g))
        draw_menu_hint();
}
