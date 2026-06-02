#include "view_utils.h"
#include "config.h"
#include "video.h"

#define BG_COLOR 0x9904u

void view_draw_background(void) {
    for (uint16_t row = 0; row < SCREEN_HEIGHT; row++)
        vg_draw_hline(0, row, SCREEN_WIDTH, BG_COLOR);
}

void view_draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color) {
    for (uint16_t row = 0; row < h; row++)
        vg_draw_hline(x, y + row, w, color);
}
