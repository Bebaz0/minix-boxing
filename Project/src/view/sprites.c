#include "sprites.h"
#include "video.h"

int draw_sprite(xpm_map_t xpm, uint16_t x, uint16_t y) {
    xpm_image_t img;
    uint8_t *raw = xpm_load(xpm, XPM_5_6_5, &img);
    if (raw == NULL) return 1;

    uint16_t *pixels = (uint16_t *)raw;
    uint32_t transparent = xpm_transparency_color(XPM_5_6_5);

    for (uint16_t row = 0; row < img.height; row++) {
        for (uint16_t col = 0; col < img.width; col++) {
            uint32_t color = pixels[row * img.width + col];
            if (color == transparent) continue;
            vg_draw_pixel(x + col, y + row, color);
        }
    }

    return 0;
}

int draw_sprite_mirrored(xpm_map_t xpm, uint16_t x, uint16_t y) {
    xpm_image_t img;
    uint8_t *raw = xpm_load(xpm, XPM_5_6_5, &img);
    if (raw == NULL) return 1;

    uint16_t *pixels = (uint16_t *)raw;
    uint32_t transparent = xpm_transparency_color(XPM_5_6_5);

    for (uint16_t row = 0; row < img.height; row++) {
        for (uint16_t col = 0; col < img.width; col++) {
            /* read from mirrored column, draw at normal column position */
            uint32_t color = pixels[row * img.width + (img.width - 1 - col)];
            if (color == transparent) continue;
            vg_draw_pixel(x + col, y + row, color);
        }
    }

    return 0;
}
