#ifndef CHAR_SELECT_H
#define CHAR_SELECT_H

#include <stdbool.h>
#include "config.h"

typedef struct {
    int  p1_char;
    int  p2_char;
    bool p1_ready;
    bool p2_ready;
} CharSelect;

/**
 * @brief Resets the character-selection state (both players on slot 0, not ready).
 *
 * @param cs Character-selection state to initialize
 */
void (char_select_init)(CharSelect *cs);

/**
 * @brief Moves Player 1's selection one slot to the left, wrapping around.
 *
 * @param cs Character-selection state to update
 */
void (char_select_p1_prev)(CharSelect *cs);

/**
 * @brief Moves Player 1's selection one slot to the right, wrapping around.
 *
 * @param cs Character-selection state to update
 */
void (char_select_p1_next)(CharSelect *cs);

/**
 * @brief Sets Player 2's selected character if the index is valid.
 *
 * @param cs Character-selection state to update
 * @param idx Character slot index in the range [0, CHAR_COUNT)
 */
void (char_select_p2_set_char)(CharSelect *cs, int idx);

/**
 * @brief Checks whether both players have confirmed their selection.
 *
 * @param cs Character-selection state to query
 * @return true if both Player 1 and Player 2 are ready
 */
bool (char_select_both_ready)(const CharSelect *cs);

#endif
