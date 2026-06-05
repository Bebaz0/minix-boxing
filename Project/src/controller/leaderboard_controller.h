#ifndef LEADERBOARD_CONTROLLER_H
#define LEADERBOARD_CONTROLLER_H

#include "controller.h"
#define SCANCODE_BREAK_MASK 0x80

/**
 * @brief Handles keyboard input on the leaderboard screen.
 *
 * Any key press returns the game to the main menu.
 *
 * @param ctrl Controller holding input state
 * @param g Game to update
 */
void leaderboard_ctrl_handle_keyboard(Controller *ctrl, Game *g);

#endif /* LEADERBOARD_CONTROLLER_H */
