#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <lcom/lcf.h>
#include <stdint.h>

/**
 * @brief Initializes graphics mode and maps VRAM into the process address space.
 *
 * Sets the requested VBE mode using a linear frame buffer, allocates the back
 * buffer and records the screen resolution and color depth.
 *
 * @param mode 16-bit VBE mode to set
 * @return Virtual address the frame buffer was mapped to, or NULL on failure
 */
void* (vg_init)(uint16_t mode);
int (video_set_mode)(uint16_t mode);

/**
 * @brief Draws a single pixel into the back buffer.
 *
 * @param x Pixel x coordinate, in screen pixels
 * @param y Pixel y coordinate, in screen pixels
 * @param color Pixel color
 * @return 0 on success, non-zero otherwise
 */
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a horizontal line of pixels into the back buffer.
 *
 * @param x Starting x coordinate, in screen pixels
 * @param y Y coordinate of the line, in screen pixels
 * @param len Line length, in pixels
 * @param color Line color
 * @return 0 on success, non-zero otherwise
 */
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a rectangular image into the back buffer.
 *
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @param width Image width, in pixels
 * @param height Image height, in pixels
 * @param pixels Pixel data, row-major, in the frame buffer's color format
 * @return 0 on success, non-zero otherwise
 */
int (vg_draw_image)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint16_t *pixels);

/**
 * @brief Draws an image into the back buffer, skipping a transparent color.
 *
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @param width Image width, in pixels
 * @param height Image height, in pixels
 * @param pixels Pixel data, row-major, in the frame buffer's color format
 * @param transparent_color Color value treated as transparent (not drawn)
 * @return 0 on success, non-zero otherwise
 */
int (vg_draw_transparent_image)(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                                const uint16_t *pixels, uint16_t transparent_color);

/**
 * @brief Copies the back buffer to the visible frame buffer (double buffering).
 */
void (vg_flip)(void);


#endif
