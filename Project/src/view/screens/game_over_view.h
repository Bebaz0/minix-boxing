#ifndef GAME_OVER_VIEW_H
#define GAME_OVER_VIEW_H

#include "game.h"

/**
 * @brief Renders the round-end / game-over screen.
 *
 * Shows the winner, the restart and menu options, and the record-name entry
 * prompt when a new leaderboard record was set.
 *
 * @param g Game to render
 */
void game_over_view_draw(const Game *g);

#endif /* GAME_OVER_VIEW_H */
