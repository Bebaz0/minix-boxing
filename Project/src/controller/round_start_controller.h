#ifndef ROUND_START_CONTROLLER_H
#define ROUND_START_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

/* Handles both GS_ROUND_START and GS_ROUND_END — both are no-op wait states. */
void round_start_ctrl_handle_keyboard(Controller *ctrl, Game *g);
void round_start_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* ROUND_START_CONTROLLER_H */
