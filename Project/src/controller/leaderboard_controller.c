#include "leaderboard_controller.h"
#include "kbc.h"

#define SCANCODE_BREAK_MASK 0x80

void leaderboard_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;

    if (scancode & SCANCODE_BREAK_MASK)
        return;

    /* any key goes back to menu; ESC is also handled globally but this catches others */
    g->state = GS_MENU;
}
