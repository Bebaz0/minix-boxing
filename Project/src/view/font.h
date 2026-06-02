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

font_t *font_create(const FontGlyphXpm *glyphs, uint32_t glyph_count, uint16_t spacing);
font_t *font_create_lcom(uint16_t spacing);
void font_set_scale(font_t *font, uint16_t scale);
void font_destroy(font_t *font);
const sprite_t *font_get_glyph(const font_t *font, char character);
uint16_t font_string_width(const font_t *font, const char *text);
uint16_t font_line_height(const font_t *font);
int font_draw_char(const font_t *font, char character, uint16_t x, uint16_t y);
int font_draw_string(const font_t *font, const char *text, uint16_t x, uint16_t y);

#endif /* FONT_H */
