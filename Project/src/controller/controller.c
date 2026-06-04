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

    if (scancode == 0x01) {
        if (g->state == GS_ACTIVE) {
            g->pause_selected = 0;
            g->state = GS_PAUSE;
        } else if (g->state == GS_PAUSE) {
            g->state = GS_ACTIVE;
        } else {
            g->state = GS_QUIT;
        }
        return;
    }

    switch (g->state) {
        case GS_MENU:        menu_ctrl_handle_keyboard(ctrl, g);        break;
        case GS_ROUND_START: round_start_ctrl_handle_keyboard(ctrl, g); break;
        case GS_ACTIVE:      active_ctrl_handle_keyboard(ctrl, g);      break;
        case GS_PAUSE:       pause_ctrl_handle_keyboard(ctrl, g);       break;
        case GS_ROUND_END:   game_over_ctrl_handle_keyboard(ctrl, g);   break;
        case GS_QUIT:        game_over_ctrl_handle_keyboard(ctrl, g);   break;
    }
}

void controller_handle_mouse(Controller *ctrl, Game *g) {
    if (!mouse_has_byte())
        return;

    uint8_t byte = get_mouse_byte();

    if (ctrl->mouse_index == 0 && !(byte & BIT(3)))
        return;

    ctrl->mouse_bytes[ctrl->mouse_index++] = byte;

    if (ctrl->mouse_index != 3)
        return;

    struct packet pkt;
    mouse_parse_packet(ctrl->mouse_bytes, &pkt);
    ctrl->mouse_index = 0;

    if (pkt.x_ov || pkt.y_ov)
        return;

    ctrl->mouse_x += pkt.delta_x * MOUSE_SENSITIVITY;
    ctrl->mouse_y -= pkt.delta_y * MOUSE_SENSITIVITY;
    ctrl->mouse_x = clamp_int(ctrl->mouse_x, 0, SCREEN_WIDTH - 1);
    ctrl->mouse_y = clamp_int(ctrl->mouse_y, 0, SCREEN_HEIGHT - 1);

    bool left_clicked  = pkt.lb && !ctrl->mouse_left_down;
    bool right_clicked = pkt.rb && !ctrl->mouse_right_down;

    ctrl->mouse_left_down  = pkt.lb;
    ctrl->mouse_right_down = pkt.rb;

    g->mouse_x = ctrl->mouse_x;
    g->mouse_y = ctrl->mouse_y;
    g->mouse_held[0] = pkt.lb;
    g->mouse_held[1] = pkt.rb;

    switch (g->state) {
        case GS_MENU:        menu_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);        break;
        case GS_ROUND_START: round_start_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked); break;
        case GS_ACTIVE:      active_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);      break;
        case GS_PAUSE:       pause_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);       break;
        case GS_ROUND_END:   game_over_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);   break;
        case GS_QUIT:        game_over_ctrl_handle_mouse(ctrl, g, left_clicked, right_clicked);   break;
    }
}
