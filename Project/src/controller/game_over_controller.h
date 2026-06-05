#ifndef GAME_OVER_CONTROLLER_H
#define GAME_OVER_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

#define SCANCODE_ENTER      0x1C
#define SCANCODE_BACKSPACE  0x0E
#define SCANCODE_W          0x11
#define SCANCODE_S          0x1F
#define SCANCODE_UP         0x48
#define SCANCODE_DOWN       0x50
#define SCANCODE_BREAK_MASK 0x80

#define END_OPTION_W      440
#define END_OPTION_H      56
#define END_OPTION_X      ((SCREEN_WIDTH - END_OPTION_W) / 2)
#define END_POPUP_H       401
#define END_POPUP_Y       ((SCREEN_HEIGHT - END_POPUP_H) / 2)
#define END_RESTART_Y     (END_POPUP_Y + 175)
#define END_MENU_Y        (END_POPUP_Y + 245)
#define REC_RESTART_Y     (END_POPUP_Y + 255)
#define REC_MENU_Y        (END_POPUP_Y + 323)

/**
 * @brief Handles keyboard input on the round-end / game-over screen.
 *
 * Drives record-name entry when a new record is set, and navigation/confirmation
 * of the restart and menu options.
 *
 * @param ctrl Controller holding input state
 * @param g Game to update
 */
void game_over_ctrl_handle_keyboard(Controller *ctrl, Game *g);

/**
 * @brief Handles mouse input on the round-end / game-over screen.
 *
 * Lets the player hover and click the restart or menu buttons.
 *
 * @param ctrl Controller holding cursor state
 * @param g Game to update
 * @param left_clicked true on a left-button press edge
 * @param right_clicked true on a right-button press edge
 */
void game_over_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* GAME_OVER_CONTROLLER_H */
