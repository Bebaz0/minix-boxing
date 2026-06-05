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

/**
 * @brief Creates a sprite by decoding an XPM image.
 *
 * @param xpm XPM image to decode
 * @return Pointer to the new sprite, or NULL on failure
 */
sprite_t *sprite_create(xpm_map_t xpm);

/**
 * @brief Creates an integer-upscaled copy of a sprite.
 *
 * @param source Sprite to scale
 * @param scale Integer scale factor
 * @return Pointer to the new scaled sprite, or NULL on failure
 */
sprite_t *sprite_create_scaled(const sprite_t *source, uint16_t scale);

/**
 * @brief Frees a sprite and its pixel buffer.
 *
 * @param sprite Sprite to destroy (NULL is ignored)
 */
void sprite_destroy(sprite_t *sprite);

/**
 * @brief Draws a sprite at its natural size, honoring its transparent color.
 *
 * @param sprite Sprite to draw
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @return 0 on success, non-zero otherwise
 */
int sprite_draw(const sprite_t *sprite, uint16_t x, uint16_t y);

/**
 * @brief Draws a sprite at its natural size without transparency.
 *
 * @param sprite Sprite to draw
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @return 0 on success, non-zero otherwise
 */
int sprite_draw_opaque(const sprite_t *sprite, uint16_t x, uint16_t y);

/**
 * @brief Draws a 1:1 cropped region of a sprite.
 *
 * @param sprite Source sprite
 * @param src_x Region left within the sprite, in pixels
 * @param src_y Region top within the sprite, in pixels
 * @param w Region width, in pixels
 * @param h Region height, in pixels
 * @param dst_x Destination left on screen, in pixels
 * @param dst_y Destination top on screen, in pixels
 * @return 0 on success, non-zero otherwise
 */
int sprite_draw_region(const sprite_t *sprite, int src_x, int src_y, uint16_t w, uint16_t h,
                       int dst_x, int dst_y);

/**
 * @brief Draws a sprite scaled to the given width and height.
 *
 * @param sprite Sprite to draw
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @param dst_w Target width, in pixels
 * @param dst_h Target height, in pixels
 * @return 0 on success, non-zero otherwise
 */
int sprite_draw_to_size(const sprite_t *sprite, int x, int y, uint16_t dst_w, uint16_t dst_h);

/**
 * @brief Draws a sprite scaled to a size and flipped horizontally.
 *
 * @param sprite Sprite to draw
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @param dst_w Target width, in pixels
 * @param dst_h Target height, in pixels
 * @return 0 on success, non-zero otherwise
 */
int sprite_draw_to_size_mirrored(const sprite_t *sprite, int x, int y, uint16_t dst_w, uint16_t dst_h);

#endif /* PROJECT_SPRITES_H */
