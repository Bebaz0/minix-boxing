#ifndef VIDEO_H
#define VIDEO_H

#include <lcom/lcf.h>

void *(vg_init)(uint16_t mode);
int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int(vg_draw_pixmap)(uint16_t x, uint16_t y, const xpm_image_t *img, const uint8_t *pixmap);

#endif
