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
int sprite_draw_region(const sprite_t *sprite, int src_x, int src_y, uint16_t w, uint16_t h,
                       int dst_x, int dst_y);
int sprite_draw_to_size(const sprite_t *sprite, int x, int y, uint16_t dst_w, uint16_t dst_h);
int sprite_draw_to_size_mirrored(const sprite_t *sprite, int x, int y, uint16_t dst_w, uint16_t dst_h);

#endif /* PROJECT_SPRITES_H */
