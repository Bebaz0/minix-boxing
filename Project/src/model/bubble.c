#include <stdlib.h>
#include "bubble.h"

void bubble_spawn(BubbleEvent *ev, int x, int y, int radius, MouseButton button, int response_window_ms) {
    /* TODO*/
    (void)ev; (void)x; (void)y; (void)radius; (void)button; (void)response_window_ms;
}

bool bubble_on_click(BubbleEvent *ev, int mx, int my, MouseButton button) {
    /* TODO */
    (void)ev; (void)mx; (void)my; (void)button;
    return false;
}

void bubble_tick(BubbleEvent *ev, int delta_ms) {
    /* TODO: Se !ev->active, não fazer nada.
       Incrementar ev->elapsed_ms += delta_ms.
       Se elapsed_ms >= response_window_ms: ev->active = false (expirou sem ser clicado). */
    (void)ev; (void)delta_ms;
}

bool bubble_failed(const BubbleEvent *ev) {
    /* TODO: Devolver true se !ev->active && !ev->hit
       (slot desativado por timeout, não por acerto). */
    (void)ev;
    return false;
}
