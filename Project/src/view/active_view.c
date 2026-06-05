#include <stdio.h>
#include "active_view.h"
#include "sprites.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"
#include "fighter_sprites.h"
#include "../assets/bubble_sprites.h"
#include "../assets/ring_sprites.h"
#include "../assets/game_background.xpm"
#include "../assets/key_sprites.h"
#include "../assets/bar_sprites.h"

#define FIGHTER_INSET 100u
#define TIMER_Y       10u

/* HUD bar frame sizes */
#define BAR_HP_W    220u
#define BAR_HP_H     28u
#define BAR_COMBO_W 170u
#define BAR_COMBO_H  20u
#define BAR_MARGIN    5u
#define BAR_GAP       4u

#define HP_FILL_X_OFF   10
#define HP_FILL_Y_OFF    5
#define HP_FILL_W      200
#define HP_FILL_H       17
#define COMBO_FILL_X_OFF 9
#define COMBO_FILL_Y_OFF 5
#define COMBO_FILL_W   152
#define COMBO_FILL_H    10

/* Bar colours */
#define COLOR_HP_FILL     0xE000u
#define COLOR_HP_EMPTY    0x2104u
#define COLOR_COMBO_FILL  0xFEA0u
#define COLOR_COMBO_EMPTY 0x2104u

/* Centros (x) das 4 lanes, distribuídos pela metade esquerda (512px). */
static const uint16_t key_lane_cx[KEY_LANE_COUNT] = {64u, 192u, 320u, 448u};



static sprite_t *get_game_background(void) {
    static sprite_t *background = NULL;

    if (background == NULL)
        background = sprite_create((xpm_map_t)game_background_xpm);

    return background;
}

void active_view_draw_background(void) {
    sprite_t *background = get_game_background();

    if (background != NULL)
        sprite_draw_opaque(background, 0, 0);
    else
        view_draw_background(0x0000u);
}

static sprite_t *get_bubble_sprite(MouseButton btn) {
    static sprite_t *bubble_left  = NULL;
    static sprite_t *bubble_right = NULL;

    if (btn == MOUSE_BUTTON_LEFT) {
        if (bubble_left == NULL)
            bubble_left = sprite_create((xpm_map_t)bubble_L);
        return bubble_left;
    }
    if (bubble_right == NULL)
        bubble_right = sprite_create((xpm_map_t)bubble_R);
    return bubble_right;
}

static sprite_t *get_ring_sprite(MouseButton btn) {
    static sprite_t *ring_left  = NULL;
    static sprite_t *ring_right = NULL;

    if (btn == MOUSE_BUTTON_LEFT) {
        if (ring_left == NULL)
            ring_left = sprite_create((xpm_map_t)ring_L);
        return ring_left;
    }
    if (ring_right == NULL)
        ring_right = sprite_create((xpm_map_t)ring_R);
    return ring_right;
}

/* Diâmetro atual do ring: encolhe de RING_START_SCALE_PCT% até ao diâmetro da
   bubble durante a fase de aproximação, ficando alinhado nos últimos
   RING_PERFECT_WINDOW_PCT% da janela (mantém-se a perfect). */
static int ring_diameter(const BubbleEvent *b) {
    int bubble_d = 2 * b->radius;
    int align_ms = b->response_window_ms * (100 - RING_PERFECT_WINDOW_PCT) / 100;

    if (align_ms <= 0 || b->elapsed_ms >= align_ms)
        return bubble_d;

    int start_d = bubble_d * RING_START_SCALE_PCT / 100;
    return bubble_d + (start_d - bubble_d) * (align_ms - b->elapsed_ms) / align_ms;
}

static sprite_t *get_bar_hp_sprite(void) {
    static sprite_t *s = NULL;
    if (s == NULL) s = sprite_create((xpm_map_t)bar_hp);
    return s;
}

static sprite_t *get_bar_combo_sprite(void) {
    static sprite_t *s = NULL;
    if (s == NULL) s = sprite_create((xpm_map_t)bar_combo);
    return s;
}

static void draw_hud_bars(const Game *g) {
    sprite_t *hp_spr    = get_bar_hp_sprite();
    sprite_t *combo_spr = get_bar_combo_sprite();

    uint16_t p1_hp_x    = BAR_MARGIN;
    uint16_t p1_combo_x = BAR_MARGIN;
    uint16_t p2_hp_x    = SCREEN_WIDTH - BAR_HP_W    - BAR_MARGIN;
    uint16_t p2_combo_x = SCREEN_WIDTH - BAR_COMBO_W - BAR_MARGIN;
    uint16_t hp_y       = BAR_MARGIN;
    uint16_t combo_y    = BAR_MARGIN + BAR_HP_H + BAR_GAP;

    int p1_hp_fill = g->p1.hp * HP_FILL_W / PLAYER_MAX_HP;
    view_draw_rect(p1_hp_x + HP_FILL_X_OFF, hp_y + HP_FILL_Y_OFF,
                   HP_FILL_W, HP_FILL_H, COLOR_HP_EMPTY);
    if (p1_hp_fill > 0)
        view_draw_rect(p1_hp_x + HP_FILL_X_OFF, hp_y + HP_FILL_Y_OFF,
                       (uint16_t)p1_hp_fill, HP_FILL_H, COLOR_HP_FILL);

    int p1_combo_fill = g->p1.combo * COMBO_FILL_W / PLAYER_MAX_COMBO;
    view_draw_rect(p1_combo_x + COMBO_FILL_X_OFF, combo_y + COMBO_FILL_Y_OFF,
                   COMBO_FILL_W, COMBO_FILL_H, COLOR_COMBO_EMPTY);
    if (p1_combo_fill > 0)
        view_draw_rect(p1_combo_x + COMBO_FILL_X_OFF, combo_y + COMBO_FILL_Y_OFF,
                       (uint16_t)p1_combo_fill, COMBO_FILL_H, COLOR_COMBO_FILL);

    int p2_hp_fill = g->p2.hp * HP_FILL_W / PLAYER_MAX_HP;
    view_draw_rect(p2_hp_x + HP_FILL_X_OFF, hp_y + HP_FILL_Y_OFF,
                   HP_FILL_W, HP_FILL_H, COLOR_HP_EMPTY);
    if (p2_hp_fill > 0)
        view_draw_rect(p2_hp_x + HP_FILL_X_OFF + (HP_FILL_W - p2_hp_fill),
                       hp_y + HP_FILL_Y_OFF,
                       (uint16_t)p2_hp_fill, HP_FILL_H, COLOR_HP_FILL);

    int p2_combo_fill = g->p2.combo * COMBO_FILL_W / PLAYER_MAX_COMBO;
    view_draw_rect(p2_combo_x + COMBO_FILL_X_OFF, combo_y + COMBO_FILL_Y_OFF,
                   COMBO_FILL_W, COMBO_FILL_H, COLOR_COMBO_EMPTY);
    if (p2_combo_fill > 0)
        view_draw_rect(p2_combo_x + COMBO_FILL_X_OFF + (COMBO_FILL_W - p2_combo_fill),
                       combo_y + COMBO_FILL_Y_OFF,
                       (uint16_t)p2_combo_fill, COMBO_FILL_H, COLOR_COMBO_FILL);

    if (hp_spr) {
        sprite_draw(hp_spr, p1_hp_x, hp_y);
        sprite_draw_to_size_mirrored(hp_spr, p2_hp_x, hp_y, hp_spr->width, hp_spr->height);
    }
    if (combo_spr) {
        sprite_draw(combo_spr, p1_combo_x, combo_y);
        sprite_draw_to_size_mirrored(combo_spr, p2_combo_x, combo_y, combo_spr->width, combo_spr->height);
    }
}

static font_t *get_hud_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(1);
        font_set_scale(font, 2);
    }

    return font;
}

static void draw_round_timer(const Game *g) {
    font_t *font = get_hud_font();
    if (font == NULL)
        return;

    int remaining = g->round_duration_ms - g->round_elapsed_ms;
    if (remaining < 0) remaining = 0;

    char buf[16];
    snprintf(buf, sizeof(buf), "%d", remaining / 1000);

    uint16_t x = (SCREEN_WIDTH - font_string_width(font, buf)) / 2;
    font_draw_string(font, buf, x, TIMER_Y);
}

static int key_lane_index(char key) {
    const char *keys = KEY_PROMPT_KEYS;
    for (int i = 0; keys[i] != '\0'; i++)
        if (keys[i] == key)
            return i;
    return -1;
}

static sprite_t *get_key_sprite(int lane) {
    static sprite_t *tiles[KEY_LANE_COUNT] = {0};

    if (lane < 0 || lane >= KEY_LANE_COUNT)
        return NULL;

    if (tiles[lane] == NULL) {
        switch (lane) {
            case 0: tiles[0] = sprite_create((xpm_map_t)key_title_Q); break;
            case 1: tiles[1] = sprite_create((xpm_map_t)key_title_W); break;
            case 2: tiles[2] = sprite_create((xpm_map_t)key_title_E); break;
            case 3: tiles[3] = sprite_create((xpm_map_t)key_title_R); break;
        }
    }

    return tiles[lane];
}

static sprite_t *get_key_target_sprite(void) {
    static sprite_t *target = NULL;

    if (target == NULL)
        target = sprite_create((xpm_map_t)key_target);

    return target;
}

static void draw_key_prompts(const Game *g) {
    sprite_t *target = get_key_target_sprite();
    int travel = KEY_HIT_ZONE_Y - KEY_LANE_TOP;

    if (target != NULL) {
        for (int lane = 0; lane < KEY_LANE_COUNT; lane++)
            sprite_draw(target, (uint16_t)(key_lane_cx[lane] - target->width / 2),
                        (uint16_t)((int)KEY_HIT_ZONE_Y - target->height / 2));
    }

    for (int i = 0; i < MAX_KEY_PROMPTS; i++) {
        const KeyPrompt *kp = &g->key_prompts[i];
        if (!kp->active)
            continue;

        int lane = key_lane_index(kp->key);
        if (lane < 0)
            continue;
        uint16_t cx = key_lane_cx[lane];

        /* O tile cai a velocidade constante e continua para lá do alvo durante a
           grace (até quase sair do ecrã) antes do prompt desaparecer. */
        int center_y = KEY_LANE_TOP;
        if (kp->response_window_ms > 0)
            center_y += travel * kp->elapsed_ms / kp->response_window_ms;
        if (center_y > SCREEN_HEIGHT)
            center_y = SCREEN_HEIGHT;

        sprite_t *tile = get_key_sprite(lane);
        if (tile != NULL)
            sprite_draw(tile, (uint16_t)(cx - tile->width / 2),
                        (uint16_t)(center_y - tile->height / 2));
    }
}

void active_view_draw(const Game *g) {
    active_view_draw_background();
    draw_hud_bars(g);

    int ft1 = char_get_fighter_type(g->char_select.p1_char);
    int ft2 = char_get_fighter_type(g->char_select.p2_char);
    sprite_t *s1 = fighter_get_idle_sprite(ft1, g->p1.anim_frame);
    sprite_t *s2 = fighter_get_idle_sprite(ft2, g->p2.anim_frame);

    int w1 = fighter_w(ft1), h1 = fighter_h(ft1);
    int w2 = fighter_w(ft2), h2 = fighter_h(ft2);

    if (s1 != NULL) {
        int x = FIGHTER_INSET + (FIGHTER_W - w1) / 2;
        sprite_draw_to_size(s1, x, SCREEN_HEIGHT - h1, w1, h1);
    }
    if (s2 != NULL) {
        int x = SCREEN_WIDTH - FIGHTER_INSET - FIGHTER_W + (FIGHTER_W - w2) / 2;
        sprite_draw_to_size_mirrored(s2, x, SCREEN_HEIGHT - h2, w2, h2);
    }

    for (int i = 0; i < MAX_BUBBLES; i++) {
        const BubbleEvent *b = &g->bubbles[i];
        if (!b->active) continue;

        int ring_d = ring_diameter(b);
        sprite_draw_to_size(get_ring_sprite(b->button),
                            b->x - ring_d / 2, b->y - ring_d / 2,
                            (uint16_t)ring_d, (uint16_t)ring_d);

        sprite_draw(get_bubble_sprite(b->button),
                    (uint16_t)(b->x - b->radius),
                    (uint16_t)(b->y - b->radius));
    }
    draw_key_prompts(g);
    draw_round_timer(g);
}
