#ifndef ACTIVE_CONTROLLER_H
#define ACTIVE_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

/**
 * @brief Handles keyboard input during active gameplay.
 *
 * Maps the current scancode to a lane key and forwards it to the game as a
 * Player 1 key press against the active key prompts.
 *
 * @param ctrl Controller holding input state
 * @param g Game to update
 */
void active_ctrl_handle_keyboard(Controller *ctrl, Game *g);

/**
 * @brief Handles mouse input during active gameplay.
 *
 * Forwards a left or right click at the cursor position to the game as a
 * Player 2 attempt against the active bubbles.
 *
 * @param ctrl Controller holding cursor state
 * @param g Game to update
 * @param left_clicked true on a left-button press edge
 * @param right_clicked true on a right-button press edge
 */
void active_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* ACTIVE_CONTROLLER_H */
