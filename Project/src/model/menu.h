#ifndef MENU_H
#define MENU_H

typedef enum {
    MENU_OPTION_START,
    MENU_OPTION_INSTRUCTIONS,
    MENU_OPTION_EXIT,
    MENU_OPTION_COUNT
} MenuOption;

typedef struct {
    MenuOption selected;
} Menu;

#define MENU_BUTTON_X 347
#define MENU_BUTTON_W 330
#define MENU_BUTTON_H 82
#define MENU_START_Y 405
#define MENU_INSTRUCTIONS_Y 493
#define MENU_EXIT_Y  581

void menu_init(Menu *menu);
void menu_select_next(Menu *menu);
void menu_select_previous(Menu *menu);
void menu_select(Menu *menu, MenuOption option);
MenuOption menu_option_at(int x, int y);

#endif /* MENU_H */
