#include "round_start_controller.h"

/* Both GS_ROUND_START and GS_ROUND_END are timer-driven; game_update() advances
   the state automatically. No user input is accepted. */

void round_start_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;
    (void)g;
}

void round_start_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked) {
    (void)ctrl;
    (void)g;
    (void)left_clicked;
    (void)right_clicked;
}
