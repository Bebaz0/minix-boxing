#ifndef PAUSE_CONTROLLER_H
#define PAUSE_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

#define SCANCODE_ENTER      0x1C
#define SCANCODE_W          0x11
#define SCANCODE_S          0x1F
#define SCANCODE_UP         0x48
#define SCANCODE_DOWN       0x50
#define SCANCODE_BREAK_MASK 0x80

#define PAUSE_OPTION_W      440
#define PAUSE_OPTION_H      56
#define PAUSE_OPTION_X      ((SCREEN_WIDTH - PAUSE_OPTION_W) / 2)
#define PAUSE_POPUP_H       401
#define PAUSE_POPUP_Y       ((SCREEN_HEIGHT - PAUSE_POPUP_H) / 2)
#define PAUSE_RESUME_Y      (PAUSE_POPUP_Y + 175)
#define PAUSE_EXIT_Y        (PAUSE_POPUP_Y + 245)

void pause_ctrl_handle_keyboard(Controller *ctrl, Game *g);
void pause_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* PAUSE_CONTROLLER_H */
