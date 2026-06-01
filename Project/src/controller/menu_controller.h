#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

void menu_ctrl_handle_keyboard(Controller *ctrl, Game *g);
void menu_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* MENU_CONTROLLER_H */
