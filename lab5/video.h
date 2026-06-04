#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <lcom/lcf.h>
#include <stdint.h>

void* (vg_init)(uint16_t mode);
int (video_set_mode)(uint16_t mode);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_image)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *pixels);
void (vg_flip)(void);


#endif
