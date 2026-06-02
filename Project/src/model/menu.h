#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU_OPTION_START,
    MENU_OPTION_EXIT,
    MENU_OPTION_COUNT
} MenuOption;

typedef struct {
    MenuOption selected;
} Menu;

#define MENU_BUTTON_X 392
#define MENU_BUTTON_W 240
#define MENU_BUTTON_H 56
#define MENU_START_Y 316
#define MENU_EXIT_Y  396

void menu_init(Menu *menu);
void menu_select_next(Menu *menu);
void menu_select_previous(Menu *menu);
void menu_select(Menu *menu, MenuOption option);
MenuOption menu_option_at(int x, int y);

#endif /* MENU_H */
