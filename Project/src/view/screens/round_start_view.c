#include "round_start_view.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"
#include "sprites.h"
#include "active_view.h"
#include "../../assets/rounds/round_1.xpm"
#include "../../assets/rounds/round_2.xpm"
#include "../../assets/rounds/round_3.xpm"
#include "../../assets/rounds/round_4.xpm"
#include "../../assets/rounds/round_5.xpm"
#include "../../assets/rounds/round_6.xpm"

#define ROUND_SPLASH_SCALE 2

static font_t *get_countdown_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(0);
        font_set_scale(font, 10);
    }

    return font;
}

static sprite_t *get_round_sprite(int round_number) {
    static sprite_t *base_sprites[6] = {NULL};
    static sprite_t *scaled_sprites[6] = {NULL};
    xpm_map_t maps[6] = {
        round_1_xpm,
        round_2_xpm,
        round_3_xpm,
        round_4_xpm,
        round_5_xpm,
        round_6_xpm
    };
    int index = round_number - 1;

    if (index < 0)
        index = 0;
    if (index > 5)
        index = 5;

    if (base_sprites[index] == NULL)
        base_sprites[index] = sprite_create(maps[index]);

    if (base_sprites[index] == NULL)
        return NULL;

    if (scaled_sprites[index] == NULL)
        scaled_sprites[index] = sprite_create_scaled(base_sprites[index], ROUND_SPLASH_SCALE);

    return scaled_sprites[index] != NULL ? scaled_sprites[index] : base_sprites[index];
}

static void draw_round_splash(const Game *g) {
    sprite_t *sprite = get_round_sprite(g->round_number);

    if (sprite == NULL)
        return;

    sprite_draw(sprite,
                (SCREEN_WIDTH - sprite->width) / 2,
                (SCREEN_HEIGHT - sprite->height) / 2);
}

void round_start_view_draw(const Game *g) {
    active_view_draw_background();

    if (g->state_timer_ms <= ROUND_SPLASH_MS) {
        draw_round_splash(g);
        return;
    }

    font_t *font = get_countdown_font();
    if (font == NULL)
        return;

    int digit = ((g->state_timer_ms - ROUND_SPLASH_MS) + 999) / 1000;
    if (digit < 1) digit = 1;
    if (digit > 3) digit = 3;

    char str[2] = {'0' + digit, '\0'};

    uint16_t x = (SCREEN_WIDTH  - font_string_width(font, str)) / 2;
    uint16_t y = (SCREEN_HEIGHT - font_line_height(font))       / 2;

    font_draw_string(font, str, x, y);
}
