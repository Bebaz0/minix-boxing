#ifndef BUBBLE_H
#define BUBBLE_H

#include <stdbool.h>
#include "config.h"

typedef enum {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT
} MouseButton;

typedef struct {
    int  x, y, radius;
    MouseButton button;
    int  response_window_ms;
    int  elapsed_ms;
    bool active;            /* slot em uso */
    bool hit;               /* foi clicado a tempo */
    bool perfect;           /* hit antes do threshold de perfeição */
} BubbleEvent;

/**
 * @brief Spawns (activates) a bubble timing event at a given position.
 *
 * @param ev Bubble event to initialize
 * @param x Center x coordinate of the bubble, in screen pixels
 * @param y Center y coordinate of the bubble, in screen pixels
 * @param radius Click-detection radius, in pixels
 * @param button Mouse button the player must use to hit it
 * @param response_window_ms Time window during which the bubble can be hit
 */
void bubble_spawn(BubbleEvent *ev, int x, int y, int radius, MouseButton button, int response_window_ms);

/**
 * @brief Tests a mouse click against the bubble and records the outcome.
 *
 * A click inside the radius with the matching button deactivates the bubble and
 * flags it as a perfect or normal hit depending on the timing window.
 *
 * @param ev Bubble event being clicked
 * @param mx Cursor x coordinate, in screen pixels
 * @param my Cursor y coordinate, in screen pixels
 * @param button Mouse button that was pressed
 * @return true if the bubble was clicked
 */
bool bubble_on_click(BubbleEvent *ev, int mx, int my, MouseButton button); /* true se a bubble foi clicada */

/**
 * @brief Advances the bubble's elapsed time and deactivates it on timeout.
 *
 * @param ev Bubble event to update
 * @param delta_ms Elapsed time since the last tick, in milliseconds
 */
void bubble_tick(BubbleEvent *ev, int delta_ms);       /* desativa se o tempo expirar */

/**
 * @brief Checks whether the bubble expired without being hit.
 *
 * @param ev Bubble event to query
 * @return true if the bubble is inactive due to timeout (not a hit)
 */
bool bubble_failed(const BubbleEvent *ev);             /* inativo por timeout, não por acerto */

#endif /* BUBBLE_H */
