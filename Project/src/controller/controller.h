#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdint.h>
#include <stdbool.h>

#include "game.h"

typedef struct {
    int mouse_x;
    int mouse_y;
    uint8_t mouse_bytes[3];
    int mouse_index;
    bool mouse_left_down;
    bool mouse_right_down;
} Controller;

void controller_init(Controller *ctrl);
void controller_handle_keyboard(Controller *ctrl, Game *g);
void controller_handle_mouse(Controller *ctrl, Game *g);

#endif /* CONTROLLER_H */
