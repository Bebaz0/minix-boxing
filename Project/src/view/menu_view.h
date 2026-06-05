#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <stdbool.h>
#include <stdint.h>

#include "game.h"

bool menu_view_hint_visible(const Game *g);
void menu_view_draw(const Game *g);
void menu_view_restore_region(const Game *g, int x, int y, uint16_t w, uint16_t h);

#endif /* MENU_VIEW_H */
