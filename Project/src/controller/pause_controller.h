#ifndef PAUSE_CONTROLLER_H
#define PAUSE_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

void pause_ctrl_handle_keyboard(Controller *ctrl, Game *g);
void pause_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* PAUSE_CONTROLLER_H */
