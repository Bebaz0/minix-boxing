#ifndef ACTIVE_CONTROLLER_H
#define ACTIVE_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

void active_ctrl_handle_keyboard(Controller *ctrl, Game *g);
void active_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* ACTIVE_CONTROLLER_H */
