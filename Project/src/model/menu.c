#include <stdbool.h>

#include "menu.h"

void menu_init(Menu *menu) {
    menu->selected = MENU_OPTION_START;
}

void menu_select_next(Menu *menu) {
    menu->selected = (MenuOption)((menu->selected + 1) % MENU_OPTION_COUNT);
}

void menu_select_previous(Menu *menu) {
    menu->selected = (MenuOption)((menu->selected + MENU_OPTION_COUNT - 1) % MENU_OPTION_COUNT);
}

void menu_select(Menu *menu, MenuOption option) {
    if (option < MENU_OPTION_COUNT)
        menu->selected = option;
}

MenuOption menu_option_at(int x, int y) {
    bool inside_x = x >= MENU_BUTTON_X && x < MENU_BUTTON_X + MENU_BUTTON_W;

    if (inside_x && y >= MENU_START_Y && y < MENU_START_Y + MENU_BUTTON_H)
        return MENU_OPTION_START;

    if (inside_x && y >= MENU_EXIT_Y && y < MENU_EXIT_Y + MENU_BUTTON_H)
        return MENU_OPTION_EXIT;

    return MENU_OPTION_COUNT;
}
