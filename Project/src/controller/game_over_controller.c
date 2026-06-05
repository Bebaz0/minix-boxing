#include "game_over_controller.h"
#include "kbc.h"
#include "config.h"

#define SCANCODE_ENTER      0x1C
#define SCANCODE_W          0x11
#define SCANCODE_S          0x1F
#define SCANCODE_UP         0x48
#define SCANCODE_DOWN       0x50
#define SCANCODE_BREAK_MASK 0x80

#define END_OPTION_W      440
#define END_OPTION_H      56
#define END_OPTION_X      ((SCREEN_WIDTH - END_OPTION_W) / 2)
#define END_POPUP_H       401
#define END_POPUP_Y       ((SCREEN_HEIGHT - END_POPUP_H) / 2)
#define END_RESTART_Y     (END_POPUP_Y + 175)
#define END_MENU_Y        (END_POPUP_Y + 245)

static int end_option_at(int x, int y) {
    if (x >= END_OPTION_X && x < END_OPTION_X + END_OPTION_W) {
        if (y >= END_RESTART_Y && y < END_RESTART_Y + END_OPTION_H) return 0;
        if (y >= END_MENU_Y    && y < END_MENU_Y    + END_OPTION_H) return 1;
    }
    return -1;
}

static void apply_end_selection(Game *g) {
    if (g->round_end_selected == 0)
        game_reset_round(g);
    else
        game_init(g);
}

void game_over_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;

    if (scancode & SCANCODE_BREAK_MASK)
        return;

    switch (scancode) {
        case SCANCODE_W:
        case SCANCODE_UP:
            g->round_end_selected = 0;
            break;
        case SCANCODE_S:
        case SCANCODE_DOWN:
            g->round_end_selected = 1;
            break;
        case SCANCODE_ENTER:
            apply_end_selection(g);
            break;
        default:
            break;
    }
}

void game_over_ctrl_handle_mouse(Controller *ctrl, Game *g,
                                 bool left_clicked, bool right_clicked) {
    (void)right_clicked;

    int option = end_option_at(ctrl->mouse_x, ctrl->mouse_y);
    if (option >= 0)
        g->round_end_selected = option;

    if (left_clicked && option >= 0)
        apply_end_selection(g);
}
