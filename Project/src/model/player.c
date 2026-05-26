#include "player.h"

void player_init(Player *p) {
    /* TODO: Inicializar hp=PLAYER_MAX_HP, combo=0, anim=ANIM_IDLE. */
}

void player_take_damage(Player *p, int dmg) {
    /* TODO: Subtrair dmg ao hp.
       Garantir que hp não fica abaixo de 0.
       Atualizar anim para ANIM_HIT. */
}

void player_add_combo(Player *p, int pts) {
    /* TODO: Adicionar pts ao combo.
       Limitar o combo a PLAYER_MAX_COMBO. */
}

void player_reset_combo(Player *p) {
    /* TODO: Repor combo a 0. */
}

bool player_is_dead(const Player *p) {
    /* TODO: Devolver true se hp <= 0. */
    return false;
}

bool player_combo_full(const Player *p) {
    /* TODO: Devolver true se combo >= PLAYER_MAX_COMBO. */
    return false;
}
