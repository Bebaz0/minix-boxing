#ifndef FONT_H
#define FONT_H

#include <lcom/lcf.h>
#include <stdint.h>

#include "sprites.h"

typedef struct {
    char character;
    xpm_map_t xpm;
} FontGlyphXpm;

typedef struct {
    char character;
    sprite_t *base_sprite;
    sprite_t *draw_sprite;
} FontGlyph;

typedef struct {
    FontGlyph *glyphs;
    uint32_t glyph_count;
    uint16_t spacing;
    uint16_t scale;
} font_t;

/**
 * @brief Creates a font from a table of per-character XPM glyphs.
 *
 * @param glyphs Array mapping characters to their glyph XPMs
 * @param glyph_count Number of entries in the array
 * @param spacing Base spacing between glyphs, in pixels
 * @return Pointer to the new font, or NULL on failure
 */
font_t *font_create(const FontGlyphXpm *glyphs, uint32_t glyph_count, uint16_t spacing);

/**
 * @brief Creates the built-in LCOM glyph font.
 *
 * @param spacing Base spacing between glyphs, in pixels
 * @return Pointer to the new font, or NULL on failure
 */
font_t *font_create_lcom(uint16_t spacing);

/**
 * @brief Sets the integer scale factor applied when drawing the font.
 *
 * @param font Font to configure
 * @param scale Integer scale factor
 */
void font_set_scale(font_t *font, uint16_t scale);

/**
 * @brief Frees a font and all of its glyph sprites.
 *
 * @param font Font to destroy (NULL is ignored)
 */
void font_destroy(font_t *font);

/**
 * @brief Looks up the (scaled) sprite for a character.
 *
 * @param font Font to query
 * @param character Character to look up
 * @return Pointer to the glyph sprite, or NULL if not present
 */
const sprite_t *font_get_glyph(const font_t *font, char character);

/**
 * @brief Computes the pixel width a string would occupy when drawn.
 *
 * @param font Font used for measurement
 * @param text Null-terminated string to measure
 * @return Width of the string, in pixels
 */
uint16_t font_string_width(const font_t *font, const char *text);

/**
 * @brief Returns the line height of the font at its current scale.
 *
 * @param font Font to query
 * @return Line height, in pixels
 */
uint16_t font_line_height(const font_t *font);

/**
 * @brief Draws a single character at the given position.
 *
 * @param font Font to draw with
 * @param character Character to draw
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @return 0 on success, non-zero otherwise
 */
int font_draw_char(const font_t *font, char character, uint16_t x, uint16_t y);

/**
 * @brief Draws a string left-to-right at the given position.
 *
 * @param font Font to draw with
 * @param text Null-terminated string to draw
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @return 0 on success, non-zero otherwise
 */
int font_draw_string(const font_t *font, const char *text, uint16_t x, uint16_t y);

/**
 * @brief Draws a string recolored to a solid color.
 *
 * @param font Font to draw with
 * @param text Null-terminated string to draw
 * @param x Top-left x coordinate, in screen pixels
 * @param y Top-left y coordinate, in screen pixels
 * @param color Color to tint the glyphs with
 * @return 0 on success, non-zero otherwise
 */
int font_draw_string_color(const font_t *font, const char *text, uint16_t x, uint16_t y, uint32_t color);

#endif /* FONT_H */
