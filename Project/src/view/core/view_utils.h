#ifndef VIEW_UTILS_H
#define VIEW_UTILS_H

#include <stdint.h>

#define BG_COLOR           0x9904u   /* dark grey-red arena */
#define BG_COLOR_ROUND_END 0xDB2Cu   /* lighter red for round end */

/**
 * @brief Fills the entire screen with a solid color.
 *
 * @param color Fill color
 */
void view_draw_background(uint32_t color);

/**
 * @brief Draws a filled rectangle.
 *
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @param w Rectangle width, in pixels
 * @param h Rectangle height, in pixels
 * @param color Fill color
 */
void view_draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color);

#endif /* VIEW_UTILS_H */
