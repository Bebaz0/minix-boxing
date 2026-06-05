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

/**
 * @brief Initializes the controller, centering the cursor and clearing state.
 *
 * @param ctrl Controller to initialize
 */
void controller_init(Controller *ctrl);

/**
 * @brief Processes the latest keyboard scancode and routes it to the game.
 *
 * Handles ESC globally (pause / back / quit) and otherwise dispatches the
 * scancode to the handler for the current game state.
 *
 * @param ctrl Controller holding input state
 * @param g Game to update
 */
void controller_handle_keyboard(Controller *ctrl, Game *g);

/**
 * @brief Assembles mouse packet bytes and routes click/movement to the game.
 *
 * Buffers the 3-byte packet, updates the clamped cursor position and edge-detects
 * button presses, then dispatches them to the handler for the current state.
 *
 * @param ctrl Controller holding input and cursor state
 * @param g Game to update
 */
void controller_handle_mouse(Controller *ctrl, Game *g);

#endif /* CONTROLLER_H */
