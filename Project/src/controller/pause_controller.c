#include "pause_controller.h"

void pause_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;
    (void)g;
    /* TODO: ESC (scancode 0x01) to resume → g->state = GS_ACTIVE */
}

void pause_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked) {
    (void)ctrl;
    (void)g;
    (void)left_clicked;
    (void)right_clicked;
}
