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

void game_over_ctrl_handle_keyboard(Controller *ctrl, Game *g);
void game_over_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* GAME_OVER_CONTROLLER_H */
