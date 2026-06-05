#ifndef CHAR_SELECT_CONTROLLER_H
#define CHAR_SELECT_CONTROLLER_H
  
#include <stdbool.h>
#include "controller.h"
#include "player.h"

/**
 * @brief Handles keyboard input on the character-selection screen.
 *
 * Moves Player 1's selection and toggles the ready state; starts the match once
 * both players are ready.
 *
 * @param ctrl Controller holding input state
 * @param g Game to update
 */
void (char_select_ctrl_handle_keyboard)(Controller *ctrl, Game *g);

/**
 * @brief Handles mouse input on the character-selection screen.
 *
 * Lets Player 2 pick a character box and toggle ready by clicking.
 *
 * @param ctrl Controller holding cursor state
 * @param g Game to update
 * @param left_clicked true on a left-button press edge
 * @param right_clicked true on a right-button press edge
 */
void (char_select_ctrl_handle_mouse)(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);
  
#endif
