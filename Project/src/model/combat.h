#ifndef COMBAT_H
#define COMBAT_H

#include <stdbool.h>
#include "player.h"

void combat_resolve(Player *self, Player *opp, bool success, bool perfect);

#endif /* COMBAT_H */
