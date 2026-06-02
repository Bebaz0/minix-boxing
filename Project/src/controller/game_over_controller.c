#include "game_over_controller.h"

void game_over_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;
    (void)g;
    /* TODO: any key returns to GS_MENU */
}

void game_over_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked) {
    (void)ctrl;
    (void)g;
    (void)left_clicked;
    (void)right_clicked;
    /* TODO: click returns to GS_MENU */
}
