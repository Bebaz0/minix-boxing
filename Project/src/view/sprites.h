#ifndef SPRITES_H
#define SPRITES_H

#include <lcom/lcf.h>
#include <stdint.h>

int draw_sprite(xpm_map_t xpm, uint16_t x, uint16_t y);
int draw_sprite_mirrored(xpm_map_t xpm, uint16_t x, uint16_t y);

#endif /* SPRITES_H */
