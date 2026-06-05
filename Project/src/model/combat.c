#include "combat.h"

void combat_resolve(Player *self, Player *opp, bool success, bool perfect) {
    if (!success) {
        player_take_damage(self, NORMAL_DAMAGE);
        self->anim = ANIM_DEFENSE;
        self->anim_frame = 0;
        return;
    }

    if (perfect) {
        self->anim = ANIM_PUNCH;
        self->anim_frame = 0;
        player_add_combo(self, PLAYER_MAX_COMBO / 8);

        if (player_combo_full(self)) {
            player_take_damage(opp, COMBO_DAMAGE);
            opp->anim = ANIM_DEFENSE;
            opp->anim_frame = 0;
            player_reset_combo(self);
            self->anim = ANIM_SPECIAL;
            self->anim_frame = 0;
        }
    }
}
