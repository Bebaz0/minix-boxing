#include "player.h"

void player_init(Player *p) {
    p->hp    = PLAYER_MAX_HP;
    p->combo = 0;
    p->anim  = ANIM_IDLE;
    p->anim_frame = 0;
    p->anim_timer_ms = 0;
}

void player_take_damage(Player *p, int dmg) {
    p->hp -= dmg;
    if (p->hp < 0)
        p->hp = 0;
}

void player_add_combo(Player *p, int pts) {
    p->combo += pts;
    if (p->combo > PLAYER_MAX_COMBO)
        p->combo = PLAYER_MAX_COMBO;
}

void player_reset_combo(Player *p) {
    p->combo = 0;
}

bool player_is_dead(const Player *p) {
    if (p->hp <= 0)
    {
        return true;
    }
    
    return false;
}

bool player_combo_full(const Player *p) {
    if (p->combo >= PLAYER_MAX_COMBO)
    {
        return true;
    }
    
    return false;
}
