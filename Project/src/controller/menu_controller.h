#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

#define SCANCODE_ENTER      0x1C
#define SCANCODE_W          0x11
#define SCANCODE_S          0x1F
#define SCANCODE_UP         0x48
#define SCANCODE_DOWN       0x50
#define SCANCODE_L          0x26   /* debug: open leaderboard */
#define SCANCODE_BREAK_MASK 0x80

/**
 * @brief Handles keyboard input on the main menu.
 *
 * Moves the selection with the arrow/W/S keys and activates the highlighted
 * option with ENTER.
 *
 * @param ctrl Controller holding input state
 * @param g Game to update
 */
void menu_ctrl_handle_keyboard(Controller *ctrl, Game *g);

/**
 * @brief Handles mouse input on the main menu.
 *
 * Highlights the menu button under the cursor and activates it on a left click.
 *
 * @param ctrl Controller holding cursor state
 * @param g Game to update
 * @param left_clicked true on a left-button press edge
 * @param right_clicked true on a right-button press edge
 */
void menu_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* MENU_CONTROLLER_H */
