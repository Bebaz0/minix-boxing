#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <stdbool.h>
#include <stdint.h>

#include "game.h"

/**
 * @brief Returns whether the blinking menu hint text is currently visible.
 *
 * @param g Game holding the menu blink timer
 * @return true while the hint should be shown in the current blink phase
 */
bool menu_view_hint_visible(const Game *g);

/**
 * @brief Renders the main menu screen.
 *
 * @param g Game to render
 */
void menu_view_draw(const Game *g);

/**
 * @brief Redraws a rectangular region of the menu background.
 *
 * Used to restore the area previously covered by the cursor before drawing it
 * at its new position.
 *
 * @param g Game to render from
 * @param x Region left, in screen pixels
 * @param y Region top, in screen pixels
 * @param w Region width, in pixels
 * @param h Region height, in pixels
 */
void menu_view_restore_region(const Game *g, int x, int y, uint16_t w, uint16_t h);

#endif /* MENU_VIEW_H */
