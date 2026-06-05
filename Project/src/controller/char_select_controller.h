#ifndef CHAR_SELECT_CONTROLLER_H
#define CHAR_SELECT_CONTROLLER_H
  
#include <stdbool.h>
#include "controller.h"
#include "player.h"

void (char_select_ctrl_handle_keyboard)(Controller *ctrl, Game *g);
void (char_select_ctrl_handle_mouse)(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);
  
#endif
