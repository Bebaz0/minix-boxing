#include "sprites.h"
#include "video.h"
#include <stdlib.h>
#include <string.h>

sprite_t *sprite_create(xpm_map_t xpm) {
    xpm_image_t img;
    uint8_t *raw = xpm_load(xpm, XPM_5_6_5, &img);
    if (raw == NULL) return NULL;

    sprite_t *s = malloc(sizeof(sprite_t));
    if (s == NULL) return NULL;

    size_t npixels = (size_t)img.width * img.height;
    s->pixels = malloc(npixels * sizeof(uint16_t));
    if (s->pixels == NULL) { free(s); return NULL; }

    s->width  = img.width;
    s->height = img.height;
    memcpy(s->pixels, raw, npixels * sizeof(uint16_t));
    return s;
}

sprite_t *sprite_create_scaled(const sprite_t *base, uint16_t scale) {
    if (base == NULL || scale == 0) return NULL;

    sprite_t *s = malloc(sizeof(sprite_t));
    if (s == NULL) return NULL;

    s->width  = base->width  * scale;
    s->height = base->height * scale;
    s->pixels = malloc((size_t)s->width * s->height * sizeof(uint16_t));
    if (s->pixels == NULL) { free(s); return NULL; }

    for (uint16_t row = 0; row < base->height; row++) {
        for (uint16_t col = 0; col < base->width; col++) {
            uint16_t color = base->pixels[row * base->width + col];
            for (uint16_t sr = 0; sr < scale; sr++)
                for (uint16_t sc = 0; sc < scale; sc++)
                    s->pixels[(row * scale + sr) * s->width + (col * scale + sc)] = color;
        }
    }
    return s;
}

void sprite_destroy(sprite_t *s) {
    if (s == NULL) return;
    free(s->pixels);
    free(s);
}

int sprite_draw(const sprite_t *s, uint16_t x, uint16_t y) {
    if (s == NULL) return 1;
    uint32_t transparent = xpm_transparency_color(XPM_5_6_5);
    for (uint16_t row = 0; row < s->height; row++)
        for (uint16_t col = 0; col < s->width; col++) {
            uint32_t color = s->pixels[row * s->width + col];
            if (color != transparent)
                vg_draw_pixel(x + col, y + row, color);
        }
    return 0;
}

int sprite_draw_mirrored(const sprite_t *s, uint16_t x, uint16_t y) {
    if (s == NULL) return 1;
    uint32_t transparent = xpm_transparency_color(XPM_5_6_5);
    for (uint16_t row = 0; row < s->height; row++)
        for (uint16_t col = 0; col < s->width; col++) {
            uint32_t color = s->pixels[row * s->width + (s->width - 1 - col)];
            if (color != transparent)
                vg_draw_pixel(x + col, y + row, color);
        }
    return 0;
}

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
