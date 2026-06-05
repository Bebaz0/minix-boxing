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
#define MENU_INSTRUCTIONS_Y 489
#define MENU_EXIT_Y  577

/**
 * @brief Initializes the menu with the START option selected.
 *
 * @param menu Menu to initialize
 */
void menu_init(Menu *menu);

/**
 * @brief Moves the selection to the next option, wrapping around.
 *
 * @param menu Menu to update
 */
void menu_select_next(Menu *menu);

/**
 * @brief Moves the selection to the previous option, wrapping around.
 *
 * @param menu Menu to update
 */
void menu_select_previous(Menu *menu);

/**
 * @brief Sets the selected menu option directly, if valid.
 *
 * @param menu Menu to update
 * @param option Option to select
 */
void menu_select(Menu *menu, MenuOption option);

/**
 * @brief Hit-tests a screen position against the menu buttons.
 *
 * @param x Cursor x coordinate, in screen pixels
 * @param y Cursor y coordinate, in screen pixels
 * @return The MenuOption under the position, or MENU_OPTION_COUNT if none
 */
MenuOption menu_option_at(int x, int y);

#endif /* MENU_H */
