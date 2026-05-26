#include "combat.h"

void combat_resolve(Player *self, Player *opp, bool success, bool perfect) {
    /* TODO: Aplicar as regras de combate para um timing event resolvido:
       - !success:            player_take_damage(self, NORMAL_DAMAGE)
       - success && perfect:  player_add_combo(self, pontos)  -- TODO: definir pontos
       - success && !perfect: nada acontece
       Após player_add_combo, verificar player_combo_full(self):
         se true → player_take_damage(opp, COMBO_DAMAGE)
                   player_reset_combo(self)
                   atualizar anim de self para ANIM_ATTACK */
}
