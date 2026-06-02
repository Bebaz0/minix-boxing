#include "combat.h"

void combat_resolve(Player *self, Player *opp, bool success, bool perfect) {
    if (!success) {
        player_take_damage(self, NORMAL_DAMAGE);
        return;
    }

    if (perfect) {
        player_add_combo(self, PLAYER_MAX_COMBO / 8);

        if (player_combo_full(self)) {
            player_take_damage(opp, COMBO_DAMAGE);
            player_reset_combo(self);
            self->anim = ANIM_ATTACK;
        }
    }
}
