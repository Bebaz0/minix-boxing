#ifndef RENDER_H
#define RENDER_H

#include "game.h"

/**
 * @brief Renders one full frame for the current game state.
 *
 * Dispatches to the appropriate per-state view and flips the back buffer to the
 * screen.
 *
 * @param g Game to render
 */
void render_frame(const Game *g);

#endif /* RENDER_H */
