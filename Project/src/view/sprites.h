#ifndef PROJECT_SPRITES_H
#define PROJECT_SPRITES_H

#include <lcom/lcf.h>
#include <stdint.h>

typedef struct {
    uint16_t width;
    uint16_t height;
    uint32_t transparent_color;
    uint8_t *pixels;
} sprite_t;

sprite_t *sprite_create(xpm_map_t xpm);
sprite_t *sprite_create_scaled(const sprite_t *source, uint16_t scale);
void sprite_destroy(sprite_t *sprite);
int sprite_draw(const sprite_t *sprite, uint16_t x, uint16_t y);
int sprite_draw_mirrored(const sprite_t *sprite, uint16_t x, uint16_t y);

#endif /* PROJECT_SPRITES_H */
