#include "bubble.h"

void bubble_spawn(BubbleEvent *ev, int x, int y, int radius,
                  MouseButton button, int response_window_ms) {
    ev->x = x;
    ev->y = y;
    ev->radius = radius;
    ev->button = button;
    ev->response_window_ms = response_window_ms;
    ev->elapsed_ms = 0;
    ev->active = true;
    ev->hit = false;
    ev->perfect = false;
}

bool bubble_on_click(BubbleEvent *ev, int mx, int my, MouseButton button) {
    if (!ev->active || ev->button != button)
        return false;

    int dx = mx - ev->x;
    int dy = my - ev->y;

    if (dx * dx + dy * dy > ev->radius * ev->radius)
        return false;

    ev->hit = true;
    ev->perfect = ev->elapsed_ms < ev->response_window_ms / 2;
    ev->active = false;

    return true;
}

void bubble_tick(BubbleEvent *ev, int delta_ms) {
    if (!ev->active)
        return;

    ev->elapsed_ms += delta_ms;

    if (ev->elapsed_ms >= ev->response_window_ms)
        ev->active = false;
}

bool bubble_failed(const BubbleEvent *ev) {
    return !ev->active && !ev->hit;
}