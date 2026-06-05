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

void (char_select_init)(CharSelect *cs);
void (char_select_p1_prev)(CharSelect *cs);
void (char_select_p1_next)(CharSelect *cs);
void (char_select_p2_set_char)(CharSelect *cs, int idx);
bool (char_select_both_ready)(const CharSelect *cs);

#endif
