#ifndef SPRITES_H
#define SPRITES_H

#include <lcom/lcf.h>
#include <stdint.h>

typedef struct {
    uint16_t  width;
    uint16_t  height;
    uint16_t *pixels; /* RGB565 pixel data, width*height entries */
} sprite_t;

sprite_t *sprite_create(xpm_map_t xpm);
sprite_t *sprite_create_scaled(const sprite_t *base, uint16_t scale);
void      sprite_destroy(sprite_t *s);
int       sprite_draw(const sprite_t *s, uint16_t x, uint16_t y);
int       sprite_draw_mirrored(const sprite_t *s, uint16_t x, uint16_t y);

/* Raw-XPM convenience wrappers (re-parse on every call) */
int draw_sprite(xpm_map_t xpm, uint16_t x, uint16_t y);
int draw_sprite_mirrored(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif /* SPRITES_H */
