#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>
#include "config.h"

typedef enum {
    ANIM_IDLE,
    ANIM_ATTACK,
    ANIM_HIT,
    ANIM_WIN,
    ANIM_LOSE
} AnimState;

typedef struct {
    int       hp;
    int       combo;
    AnimState anim;
    int       anim_frame;       // 0 or 1
    int       anim_timer_ms;    // counts up
} Player;

void player_init(Player *p);
void player_reset_round_state(Player *p);
void player_take_damage(Player *p, int dmg);
void player_add_combo(Player *p, int pts);
void player_reset_combo(Player *p);
bool player_is_dead(const Player *p);
bool player_combo_full(const Player *p);

#endif /* PLAYER_H */
