#ifndef ROUND_START_CONTROLLER_H
#define ROUND_START_CONTROLLER_H

#include <stdbool.h>
#include "controller.h"

/* Handles both GS_ROUND_START and GS_ROUND_END — both are no-op wait states. */
/**
 * @brief Keyboard handler for the round-start / round-end wait states.
 *
 * These states advance on a timer, so input is ignored (no-op).
 *
 * @param ctrl Controller holding input state
 * @param g Game (unchanged)
 */
void round_start_ctrl_handle_keyboard(Controller *ctrl, Game *g);

/**
 * @brief Mouse handler for the round-start / round-end wait states.
 *
 * These states advance on a timer, so input is ignored (no-op).
 *
 * @param ctrl Controller holding cursor state
 * @param g Game (unchanged)
 * @param left_clicked true on a left-button press edge
 * @param right_clicked true on a right-button press edge
 */
void round_start_ctrl_handle_mouse(Controller *ctrl, Game *g, bool left_clicked, bool right_clicked);

#endif /* ROUND_START_CONTROLLER_H */
