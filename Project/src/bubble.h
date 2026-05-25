#ifndef BUBBLE_H
#define BUBBLE_H

#include <stdbool.h>
#include "config.h"

typedef struct {
    int  x, y, radius;
    int  response_window_ms;
    int  elapsed_ms;
    bool active;            /* slot em uso */
    bool hit;               /* foi clicado a tempo */
    bool perfect;           /* hit antes do threshold de perfeição */
} BubbleEvent;

void bubble_spawn(BubbleEvent *ev, int x, int y, int radius, int response_window_ms);
bool bubble_on_click(BubbleEvent *ev, int mx, int my); /* true se a bubble foi clicada */
void bubble_tick(BubbleEvent *ev, int delta_ms);       /* desativa se o tempo expirar */
bool bubble_failed(const BubbleEvent *ev);             /* inativo por timeout, não por acerto */

#endif /* BUBBLE_H */
