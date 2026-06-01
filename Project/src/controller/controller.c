#include <lcom/lcf.h>

#include "controller.h"
#include "config.h"
#include "kbc.h"
#include "mouse.h"
#include "menu_controller.h"
#include "active_controller.h"
#include "pause_controller.h"
#include "round_start_controller.h"
#include "game_over_controller.h"

static int clamp_int(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void controller_init(Controller *ctrl) {
    ctrl->mouse_x = SCREEN_WIDTH / 2;
    ctrl->mouse_y = SCREEN_HEIGHT / 2;
    ctrl->mouse_index = 0;
    ctrl->mouse_left_down = false;
    ctrl->mouse_right_down = false;

    for (int i = 0; i < 3; i++)
        ctrl->mouse_bytes[i] = 0;
}

void controller_handle_keyboard(Controller *ctrl, Game *g) {
    if (kbc_error)
        return;

    switch (g->state) {
        case GS_MENU:        menu_ctrl_handle_keyboard(ctrl, g);        break;
        case GS_ROUND_START: round_start_ctrl_handle_keyboard(ctrl, g); break;
        case GS_ACTIVE:      active_ctrl_handle_keyboard(ctrl, g);      break;
        case GS_PAUSE:       pause_ctrl_handle_keyboard(ctrl, g);       break;
        case GS_ROUND_END:   round_start_ctrl_handle_keyboard(ctrl, g); break;
        case GS_GAME_OVER:   game_over_ctrl_handle_keyboard(ctrl, g);   break;
    }
}

void controller_handle_mouse(Controller *ctrl, Game *g) {
    uint8_t byte = get_mouse_byte();

    if (ctrl->mouse_index == 0 && !(byte & BIT(3)))
        return;

    ctrl->mouse_bytes[ctrl->mouse_index++] = byte;

    if (ctrl->mouse_index != 3)
        return;

    struct packet pkt;
    mouse_parse_packet(ctrl->mouse_bytes, &pkt);
    ctrl->mouse_index = 0;

    ctrl->mouse_x += pkt.delta_x;
    ctrl->mouse_y -= pkt.delta_y;
    ctrl->mouse_x = clamp_int(ctrl->mouse_x, 0, SCREEN_WIDTH - 1);
    ctrl->mouse_y = clamp_int(ctrl->mouse_y, 0, SCREEN_HEIGHT - 1);

    bool left_clicked  = pkt.lb && !ctrl->mouse_left_down;
    bool right_clicked = pkt.rb && !ctrl->mouse_right_down;

    ctrl->mouse_left_down  = pkt.lb;
    ctrl->mouse_right_down = pkt.rb;

    switch (g->state) {
        case GS_MENU:        menu_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);        break;
        case GS_ROUND_START: round_start_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked); break;
        case GS_ACTIVE:      active_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);      break;
        case GS_PAUSE:       pause_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);       break;
        case GS_ROUND_END:   round_start_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked); break;
        case GS_GAME_OVER:   game_over_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);   break;
    }
}
