#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

#define SCANCODE_ENTER      0x1C
#define SCANCODE_W          0x11
#define SCANCODE_S          0x1F
#define SCANCODE_UP         0x48
#define SCANCODE_DOWN       0x50
#define SCANCODE_L          0x26   /* debug: open leaderboard */
#define SCANCODE_BREAK_MASK 0x80

void menu_ctrl_handle_keyboard(Controller *ctrl, Game *g);
void menu_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* MENU_CONTROLLER_H */
