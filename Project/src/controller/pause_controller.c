#include "pause_controller.h"
#include "kbc.h"
#include "config.h"

static int pause_option_at(int x, int y) {
    if (x >= PAUSE_OPTION_X && x < PAUSE_OPTION_X + PAUSE_OPTION_W) {
        if (y >= PAUSE_RESUME_Y && y < PAUSE_RESUME_Y + PAUSE_OPTION_H) return 0;
        if (y >= PAUSE_EXIT_Y   && y < PAUSE_EXIT_Y   + PAUSE_OPTION_H) return 1;
    }
    return -1;
}

static void apply_pause_selection(Game *g) {
    if (g->pause_selected == 0)
        g->state = GS_ACTIVE;
    else
        game_init(g);
}

void pause_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;

    if (scancode & SCANCODE_BREAK_MASK)
        return;

    switch (scancode) {
        case SCANCODE_W:
        case SCANCODE_UP:
            g->pause_selected = 0;
            break;
        case SCANCODE_S:
        case SCANCODE_DOWN:
            g->pause_selected = 1;
            break;
        case SCANCODE_ENTER:
            apply_pause_selection(g);
            break;
        default:
            break;
    }
}

void pause_ctrl_handle_mouse(Controller *ctrl, Game *g,
                             bool left_clicked, bool right_clicked) {
    (void)right_clicked;

    int option = pause_option_at(ctrl->mouse_x, ctrl->mouse_y);
    if (option >= 0)
        g->pause_selected = option;

    if (left_clicked && option >= 0)
        apply_pause_selection(g);
}
