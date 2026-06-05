#include "font.h"
#include "config.h"
#include "video.h"
#include "../assets/fonts/lcomfont.h"

#include <stdlib.h>

static const FontGlyphXpm lcomfont_glyphs[] = {
    { '!', glyph_33 },
    { '%', glyph_37 },
    { '*', glyph_42 },
    { '0', glyph_48 },
    { '1', glyph_49 },
    { '2', glyph_50 },
    { '3', glyph_51 },
    { '4', glyph_52 },
    { '5', glyph_53 },
    { '6', glyph_54 },
    { '7', glyph_55 },
    { '8', glyph_56 },
    { '9', glyph_57 },
    { ':', glyph_58 },
    { ';', glyph_59 },
    { '?', glyph_63 },
    { 'A', glyph_65 },
    { 'B', glyph_66 },
    { 'C', glyph_67 },
    { 'D', glyph_68 },
    { 'E', glyph_69 },
    { 'F', glyph_70 },
    { 'G', glyph_71 },
    { 'H', glyph_72 },
    { 'I', glyph_73 },
    { 'J', glyph_74 },
    { 'K', glyph_75 },
    { 'L', glyph_76 },
    { 'M', glyph_77 },
    { 'N', glyph_78 },
    { 'O', glyph_79 },
    { 'P', glyph_80 },
    { 'Q', glyph_81 },
    { 'R', glyph_82 },
    { 'S', glyph_83 },
    { 'T', glyph_84 },
    { 'U', glyph_85 },
    { 'V', glyph_86 },
    { 'W', glyph_87 },
    { 'X', glyph_88 },
    { 'Y', glyph_89 },
    { 'Z', glyph_90 },
    { 'a', glyph_97 },
    { 'b', glyph_98 },
    { 'c', glyph_99 },
    { 'd', glyph_100 },
    { 'e', glyph_101 },
    { 'f', glyph_102 },
    { 'g', glyph_103 },
    { 'h', glyph_104 },
    { 'i', glyph_105 },
    { 'j', glyph_106 },
    { 'k', glyph_107 },
    { 'l', glyph_108 },
    { 'm', glyph_109 },
    { 'n', glyph_110 },
    { 'o', glyph_111 },
    { 'p', glyph_112 },
    { 'q', glyph_113 },
    { 'r', glyph_114 },
    { 's', glyph_115 },
    { 't', glyph_116 },
    { 'u', glyph_117 },
    { 'v', glyph_118 },
    { 'w', glyph_119 },
    { 'x', glyph_120 },
    { 'y', glyph_121 },
    { 'z', glyph_122 },
};

#define LCOMFONT_GLYPH_COUNT (sizeof(lcomfont_glyphs) / sizeof(lcomfont_glyphs[0]))

font_t *font_create(const FontGlyphXpm *glyphs, uint32_t glyph_count, uint16_t spacing) {
    if (glyphs == NULL || glyph_count == 0)
        return NULL;

    font_t *font = malloc(sizeof(font_t));
    if (font == NULL)
        return NULL;

    font->glyphs = malloc(sizeof(FontGlyph) * glyph_count);
    if (font->glyphs == NULL) {
        free(font);
        return NULL;
    }

    font->glyph_count = glyph_count;
    font->spacing = spacing;
    font->scale = 1;

    for (uint32_t i = 0; i < glyph_count; i++) {
        font->glyphs[i].character = glyphs[i].character;
        font->glyphs[i].base_sprite = sprite_create(glyphs[i].xpm);
        font->glyphs[i].draw_sprite = font->glyphs[i].base_sprite;

        if (font->glyphs[i].base_sprite == NULL) {
            for (uint32_t j = 0; j < i; j++)
                sprite_destroy(font->glyphs[j].base_sprite);

            free(font->glyphs);
            free(font);
            return NULL;
        }
    }

    return font;
}

font_t *font_create_lcom(uint16_t spacing) {
    return font_create(lcomfont_glyphs, LCOMFONT_GLYPH_COUNT, spacing);
}

void font_set_scale(font_t *font, uint16_t scale) {
    if (font == NULL)
        return;

    font->scale = scale == 0 ? 1 : scale;

    for (uint32_t i = 0; i < font->glyph_count; i++) {
        if (font->glyphs[i].draw_sprite != font->glyphs[i].base_sprite)
            sprite_destroy(font->glyphs[i].draw_sprite);

        if (font->scale == 1) {
            font->glyphs[i].draw_sprite = font->glyphs[i].base_sprite;
        } else {
            font->glyphs[i].draw_sprite = sprite_create_scaled(font->glyphs[i].base_sprite, font->scale);
            if (font->glyphs[i].draw_sprite == NULL)
                font->glyphs[i].draw_sprite = font->glyphs[i].base_sprite;
        }
    }
}

void font_destroy(font_t *font) {
    if (font == NULL)
        return;

    for (uint32_t i = 0; i < font->glyph_count; i++) {
        if (font->glyphs[i].draw_sprite != font->glyphs[i].base_sprite)
            sprite_destroy(font->glyphs[i].draw_sprite);

        sprite_destroy(font->glyphs[i].base_sprite);
    }

    free(font->glyphs);
    free(font);
}

const sprite_t *font_get_glyph(const font_t *font, char character) {
    if (font == NULL)
        return NULL;

    for (uint32_t i = 0; i < font->glyph_count; i++) {
        if (font->glyphs[i].character == character)
            return font->glyphs[i].draw_sprite;
    }

    return NULL;
}

uint16_t font_string_width(const font_t *font, const char *text) {
    if (font == NULL || text == NULL)
        return 0;

    uint16_t width = 0;

    for (uint32_t i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') {
            width += font->spacing * 4 * font->scale;
            continue;
        }

        const sprite_t *glyph = font_get_glyph(font, text[i]);
        if (glyph == NULL)
            continue;

        width += glyph->width;
        if (text[i + 1] != '\0')
            width += font->spacing * font->scale;
    }

    return width;
}

uint16_t font_line_height(const font_t *font) {
    if (font == NULL)
        return 0;

    uint16_t height = 0;

    for (uint32_t i = 0; i < font->glyph_count; i++) {
        if (font->glyphs[i].draw_sprite != NULL && font->glyphs[i].draw_sprite->height > height)
            height = font->glyphs[i].draw_sprite->height;
    }

    return height;
}

static int font_draw_glyph_color(const sprite_t *glyph, uint16_t x, uint16_t y,
                                 uint32_t color) {
    if (glyph == NULL || glyph->pixels == NULL)
        return 1;

    uint16_t *pixels = (uint16_t *)glyph->pixels;

    for (uint16_t row = 0; row < glyph->height; row++) {
        if (y + row >= SCREEN_HEIGHT)
            break;

        for (uint16_t col = 0; col < glyph->width; col++) {
            if (x + col >= SCREEN_WIDTH)
                break;

            uint32_t pixel = pixels[row * glyph->width + col];
            if (pixel == glyph->transparent_color)
                continue;

            vg_draw_pixel(x + col, y + row, color);
        }
    }

    return 0;
}

int font_draw_char(const font_t *font, char character, uint16_t x, uint16_t y) {
    const sprite_t *glyph = font_get_glyph(font, character);
    if (glyph == NULL)
        return 1;

    return sprite_draw(glyph, x, y);
}

int font_draw_string(const font_t *font, const char *text, uint16_t x, uint16_t y) {
    if (font == NULL || text == NULL)
        return 1;

    uint16_t cursor_x = x;

    for (uint32_t i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') {
            cursor_x += font->spacing * 4 * font->scale;
            continue;
        }

        const sprite_t *glyph = font_get_glyph(font, text[i]);
        if (glyph == NULL)
            continue;

        if (sprite_draw(glyph, cursor_x, y) != 0)
            return 1;

        cursor_x += glyph->width + font->spacing * font->scale;
    }

    return 0;
}

int font_draw_string_color(const font_t *font, const char *text, uint16_t x, uint16_t y, uint32_t color) {
    if (font == NULL || text == NULL)
        return 1;

    uint16_t cursor_x = x;

    for (uint32_t i = 0; text[i] != '\0'; i++) {
        if (text[i] == ' ') {
            cursor_x += font->spacing * 4 * font->scale;
            continue;
        }

        const sprite_t *glyph = font_get_glyph(font, text[i]);
        if (glyph == NULL)
            continue;

        if (font_draw_glyph_color(glyph, cursor_x, y, color) != 0)
            return 1;

        cursor_x += glyph->width + font->spacing * font->scale;
    }

    return 0;
}
