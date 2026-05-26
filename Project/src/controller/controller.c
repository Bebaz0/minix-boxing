#include <lcom/lcf.h>

#include "controller.h"
#include "config.h"
#include "kbc.h"
#include "mouse.h"

static char controller_scancode_to_key(uint8_t code) {
    switch (code) {
        case 0x10:
            return 'Q';
        case 0x11:
            return 'W';
        case 0x12:
            return 'E';
        case 0x13:
            return 'R';
        default:
            return '\0';
    }
}

static int clamp_int(int value, int min, int max) {
    if (value < min)
        return min;
    if (value > max)
        return max;
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
    (void)ctrl;

    if (kbc_error)
        return;

    char key = controller_scancode_to_key(scancode);

    if (key != '\0')
        game_handle_key(g, key);
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

    if (pkt.lb && !ctrl->mouse_left_down)
        game_handle_click(g, ctrl->mouse_x, ctrl->mouse_y, MOUSE_BUTTON_LEFT);

    if (pkt.rb && !ctrl->mouse_right_down)
        game_handle_click(g, ctrl->mouse_x, ctrl->mouse_y, MOUSE_BUTTON_RIGHT);

    ctrl->mouse_left_down = pkt.lb;
    ctrl->mouse_right_down = pkt.rb;
}
