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

    return vg_draw_transparent_image(x, y, sprite->width, sprite->height,
                                     (uint16_t *)sprite->pixels,
                                     (uint16_t)sprite->transparent_color);
}

int sprite_draw_opaque(const sprite_t *sprite, uint16_t x, uint16_t y) {
    if (sprite == NULL || sprite->pixels == NULL)
        return 1;

    return vg_draw_image(x, y, sprite->width, sprite->height, (uint16_t *)sprite->pixels);
}

int sprite_draw_region(const sprite_t *sprite, int src_x, int src_y, uint16_t w, uint16_t h,
                       int dst_x, int dst_y) {
    if (sprite == NULL || sprite->pixels == NULL)
        return 1;

    uint16_t *pixels = (uint16_t *)sprite->pixels;

    for (uint16_t row = 0; row < h; row++) {
        int sy = src_y + row;
        int dy = dst_y + row;
        if (sy < 0 || sy >= (int)sprite->height || dy < 0 || dy >= SCREEN_HEIGHT)
            continue;

        for (uint16_t col = 0; col < w; col++) {
            int sx = src_x + col;
            int dx = dst_x + col;
            if (sx < 0 || sx >= (int)sprite->width || dx < 0 || dx >= SCREEN_WIDTH)
                continue;

            uint32_t color = pixels[sy * sprite->width + sx];
            if (color == sprite->transparent_color) continue;
            vg_draw_pixel((uint16_t)dx, (uint16_t)dy, color);
        }
    }

    return 0;
}

int sprite_draw_to_size(const sprite_t *sprite, int x, int y, uint16_t dst_w, uint16_t dst_h) {
    if (sprite == NULL || sprite->pixels == NULL || dst_w == 0 || dst_h == 0)
        return 1;

    uint16_t *pixels = (uint16_t *)sprite->pixels;
    int start_row = y < 0 ? -y : 0;
    int start_col = x < 0 ? -x : 0;
    int end_row = y + dst_h > SCREEN_HEIGHT ? SCREEN_HEIGHT - y : dst_h;
    int end_col = x + dst_w > SCREEN_WIDTH ? SCREEN_WIDTH - x : dst_w;

    if (start_row >= end_row || start_col >= end_col)
        return 0;

    for (int row = start_row; row < end_row; row++) {
        uint16_t src_row = (uint16_t)((uint32_t)row * sprite->height / dst_h);
        for (int col = start_col; col < end_col; col++) {
            uint16_t src_col = (uint16_t)((uint32_t)col * sprite->width / dst_w);
            uint32_t color = pixels[src_row * sprite->width + src_col];
            if (color == sprite->transparent_color) continue;
            vg_draw_pixel((uint16_t)(x + col), (uint16_t)(y + row), color);
        }
    }

    return 0;
}

int sprite_draw_to_size_mirrored(const sprite_t *sprite, int x, int y,
                                  uint16_t dst_w, uint16_t dst_h) {
    if (sprite == NULL || sprite->pixels == NULL || dst_w == 0 || dst_h == 0)
        return 1;

    uint16_t *pixels = (uint16_t *)sprite->pixels;

    for (uint16_t row = 0; row < dst_h; row++) {
        uint16_t src_row = (uint16_t)((uint32_t)row * sprite->height / dst_h);
        for (uint16_t col = 0; col < dst_w; col++) {
            uint16_t src_col = (uint16_t)((uint32_t)(dst_w - 1 - col) * sprite->width / dst_w);
            uint32_t color = pixels[src_row * sprite->width + src_col];
            if (color == sprite->transparent_color) continue;
            vg_draw_pixel((uint16_t)(x + col), (uint16_t)(y + row), color);
        }
    }

    return 0;
}
