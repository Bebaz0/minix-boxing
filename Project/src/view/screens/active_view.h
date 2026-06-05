#ifndef ACTIVE_VIEW_H
#define ACTIVE_VIEW_H

#include "game.h"

/**
 * @brief Renders the active combat arena (fighters, HUD bars and timing events).
 *
 * @param g Game to render
 */
void active_view_draw(const Game *g);

/**
 * @brief Draws only the static arena background of the combat screen.
 */
void active_view_draw_background(void);

#endif /* ACTIVE_VIEW_H */
