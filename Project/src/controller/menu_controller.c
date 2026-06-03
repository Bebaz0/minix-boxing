#include "menu_controller.h"
#include "kbc.h"

#define SCANCODE_ESC        0x01
#define SCANCODE_ENTER      0x1C
#define SCANCODE_W          0x11
#define SCANCODE_S          0x1F
#define SCANCODE_UP         0x48
#define SCANCODE_DOWN       0x50
#define SCANCODE_BREAK_MASK 0x80

static void menu_apply_selected(Game *g) {
    switch (g->menu.selected) {
        case MENU_OPTION_START:
            g->state = GS_ROUND_START;
            g->state_timer_ms = INTER_ROUND_MS;
            break;
        case MENU_OPTION_EXIT:
            g->state = GS_QUIT;
            break;
        case MENU_OPTION_COUNT:
            break;
    }
}

void menu_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;

    if (scancode & SCANCODE_BREAK_MASK)
        return;

    switch (scancode) {
        case SCANCODE_W:
        case SCANCODE_UP:
            menu_select_previous(&g->menu);
            break;
        case SCANCODE_S:
        case SCANCODE_DOWN:
            menu_select_next(&g->menu);
            break;
        case SCANCODE_ENTER:
            menu_apply_selected(g);
            break;
        case SCANCODE_ESC:
            g->state = GS_QUIT;
            break;
        default:
            break;
    }
}

void menu_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked) {
    (void)right_clicked;

    MenuOption option = menu_option_at(ctrl->mouse_x, ctrl->mouse_y);
    if (option != MENU_OPTION_COUNT)
        menu_select(&g->menu, option);

    if (left_clicked && option != MENU_OPTION_COUNT)
        menu_apply_selected(g);
}
