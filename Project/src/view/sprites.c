#include "sprites.h"
#include "video.h"
#include "config.h"

#include <stdlib.h>

sprite_t *sprite_create(xpm_map_t xpm) {
    xpm_image_t img;
    uint8_t *raw = xpm_load(xpm, XPM_5_6_5, &img);
    if (raw == NULL)
        return NULL;

    sprite_t *sprite = malloc(sizeof(sprite_t));
    if (sprite == NULL) {
        free(raw);
        return NULL;
    }

    sprite->width = img.width;
    sprite->height = img.height;
    sprite->transparent_color = xpm_transparency_color(XPM_5_6_5);
    sprite->pixels = raw;

    return sprite;
}

sprite_t *sprite_create_scaled(const sprite_t *source, uint16_t scale) {
    if (source == NULL || source->pixels == NULL)
        return NULL;

    if (scale == 0)
        scale = 1;

    sprite_t *sprite = malloc(sizeof(sprite_t));
    if (sprite == NULL)
        return NULL;

    sprite->width = source->width * scale;
    sprite->height = source->height * scale;
    sprite->transparent_color = source->transparent_color;
    sprite->pixels = malloc(sprite->width * sprite->height * sizeof(uint16_t));

    if (sprite->pixels == NULL) {
        free(sprite);
        return NULL;
    }

    uint16_t *src_pixels = (uint16_t *)source->pixels;
    uint16_t *dst_pixels = (uint16_t *)sprite->pixels;

    for (uint16_t row = 0; row < source->height; row++) {
        for (uint16_t col = 0; col < source->width; col++) {
            uint16_t color = src_pixels[row * source->width + col];

            for (uint16_t sy = 0; sy < scale; sy++) {
                for (uint16_t sx = 0; sx < scale; sx++) {
                    uint16_t dst_x = col * scale + sx;
                    uint16_t dst_y = row * scale + sy;
                    dst_pixels[dst_y * sprite->width + dst_x] = color;
                }
            }
        }
    }

    return sprite;
}

void sprite_destroy(sprite_t *sprite) {
    if (sprite == NULL)
        return;

    free(sprite->pixels);
    free(sprite);
}

int sprite_draw(const sprite_t *sprite, uint16_t x, uint16_t y) {
    if (sprite == NULL || sprite->pixels == NULL)
        return 1;

    uint16_t *pixels = (uint16_t *)sprite->pixels;

    for (uint16_t row = 0; row < sprite->height; row++) {
        if (y + row >= SCREEN_HEIGHT) break;
        for (uint16_t col = 0; col < sprite->width; col++) {
            if (x + col >= SCREEN_WIDTH) break;
            uint32_t color = pixels[row * sprite->width + col];
            if (color == sprite->transparent_color) continue;
            vg_draw_pixel(x + col, y + row, color);
        }
    }

    return 0;
}

int sprite_draw_mirrored(const sprite_t *sprite, uint16_t x, uint16_t y) {
    if (sprite == NULL || sprite->pixels == NULL)
        return 1;

    uint16_t *pixels = (uint16_t *)sprite->pixels;

    for (uint16_t row = 0; row < sprite->height; row++) {
        if (y + row >= SCREEN_HEIGHT) break;
        for (uint16_t col = 0; col < sprite->width; col++) {
            if (x + col >= SCREEN_WIDTH) break;
            uint32_t color = pixels[row * sprite->width + (sprite->width - 1 - col)];
            if (color == sprite->transparent_color) continue;
            vg_draw_pixel(x + col, y + row, color);
        }
    }

    return 0;
}
