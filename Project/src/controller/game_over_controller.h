#ifndef GAME_OVER_CONTROLLER_H
#define GAME_OVER_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

void game_over_ctrl_handle_keyboard(Controller *ctrl, Game *g);
void game_over_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* GAME_OVER_CONTROLLER_H */
