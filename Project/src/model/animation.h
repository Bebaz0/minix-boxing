#ifndef ANIMATION_H
#define ANIMATION_H

#include "player.h"

int animation_fighter_for_character(int char_idx);
void animation_tick_player(Player *p, int fighter_type, int delta_ms);

#endif /* ANIMATION_H */
