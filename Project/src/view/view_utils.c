#include "view_utils.h"
#include "config.h"
#include "video.h"

void view_draw_background(uint32_t color) {
    for (uint16_t row = 0; row < SCREEN_HEIGHT; row++)
        vg_draw_hline(0, row, SCREEN_WIDTH, color);
}

void view_draw_rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color) {
    for (uint16_t row = 0; row < h; row++)
        vg_draw_hline(x, y + row, w, color);
}

void view_draw_filled_circle(int cx, int cy, int r, uint32_t color) {
    for (int dy = -r; dy <= r; dy++) {
        int dx2 = r * r - dy * dy;
        int dx = 0;
        while ((dx + 1) * (dx + 1) <= dx2) dx++;
        if (cy + dy >= 0 && cy + dy < SCREEN_HEIGHT)
            vg_draw_hline(cx - dx, cy + dy, 2 * dx + 1, color);
    }
}
