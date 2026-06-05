#ifndef COMBAT_H
#define COMBAT_H

#include <stdbool.h>
#include "player.h"

/**
 * @brief Resolves the combat outcome of a timing event.
 *
 * On a miss, the acting player takes normal damage and plays the defense
 * animation. On a perfect hit, the player builds combo and plays the punch
 * animation; when the combo fills up it triggers a special that deals combo
 * damage to the opponent and resets the meter.
 *
 * @param self Player who acted on the timing event
 * @param opp Opposing player
 * @param success true if the event was hit, false if it was missed
 * @param perfect true if the hit landed in the perfect window
 */
void combat_resolve(Player *self, Player *opp, bool success, bool perfect);

#endif /* COMBAT_H */
