#include "char_select.h"
 
void (char_select_init)(CharSelect *cs){
    cs->p1_char= 0;
    cs->p2_char= 0;
    cs->p1_ready= false;
    cs->p2_ready= false;
}

void (char_select_p1_prev)(CharSelect *cs){
    if(cs->p1_char== 0)cs->p1_char= CHAR_COUNT-1;
    else cs->p1_char--;
}

void (char_select_p1_next)(CharSelect *cs){
    if(cs->p1_char == CHAR_COUNT-1)cs->p1_char= 0;
    else cs->p1_char++;
}

void (char_select_p2_set_char)(CharSelect *cs, int idx){
    if (idx>=0 && idx<CHAR_COUNT)cs->p2_char=idx;
}

bool (char_select_both_ready)(const CharSelect *cs){
    return cs->p1_ready && cs->p2_ready;
}
