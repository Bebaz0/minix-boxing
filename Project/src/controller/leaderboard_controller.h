#ifndef LEADERBOARD_CONTROLLER_H
#define LEADERBOARD_CONTROLLER_H

#include "controller.h"
#define SCANCODE_BREAK_MASK 0x80

void leaderboard_ctrl_handle_keyboard(Controller *ctrl, Game *g);

#endif /* LEADERBOARD_CONTROLLER_H */
