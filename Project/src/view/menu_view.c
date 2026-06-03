#include "menu_view.h"
#include "sprites.h"
#include "config.h"
#include "view_utils.h"
#include "../assets/menu_button_exit.xpm"
#include "../assets/menu_button_exit_selected.xpm"
#include "../assets/menu_button_instructions.xpm"
#include "../assets/menu_button_instructions_selected.xpm"
#include "../assets/menu_button_start.xpm"
#include "../assets/menu_button_start_selected.xpm"
#include "../assets/menu_background.xpm"

#define CURSOR_COLOR        0xFFFFu
#define CURSOR_SHADOW       0x0000u

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
    sprite_draw(get_menu_background_sprite(), 0, 0);
    draw_menu_button(g, MENU_OPTION_START, MENU_START_Y);
    draw_menu_button(g, MENU_OPTION_INSTRUCTIONS, MENU_INSTRUCTIONS_Y);
    draw_menu_button(g, MENU_OPTION_EXIT, MENU_EXIT_Y);
    draw_mouse_cursor(mouse_x, mouse_y);
}
