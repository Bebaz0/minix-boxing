#include <lcom/lcf.h>

#include "active_controller.h"
#include "game.h"
#include "kbc.h"
#include "mouse.h"

static char active_scancode_to_key(uint8_t code) {
    switch (code) {
        case 0x10: return 'Q';
        case 0x11: return 'W';
        case 0x12: return 'E';
        case 0x13: return 'R';
        default:   return '\0';
    }
}

void active_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;
    char key = active_scancode_to_key(scancode);
    if (key != '\0')
        game_handle_key(g, key);
}

void active_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked) {
    if (left_clicked)
        game_handle_click(g, ctrl->mouse_x, ctrl->mouse_y, MOUSE_BUTTON_LEFT);
    if (right_clicked)
        game_handle_click(g, ctrl->mouse_x, ctrl->mouse_y, MOUSE_BUTTON_RIGHT);
}
