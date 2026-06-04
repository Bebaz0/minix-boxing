#include <stdio.h>
#include "active_view.h"
#include "sprites.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"
#include "../assets/fighter.h"
#include "../assets/bubble_sprites.h"
#include "../assets/ring_sprites.h"
#include "../assets/key_sprites.h"

#define FIGHTER_Y     300u
#define FIGHTER_INSET 100u
#define TIMER_Y       10u

#define WASD_KEY_SIZE  50u
#define WASD_GAP        4u
#define WASD_X         50u
#define WASD_Y        660u

#define WASD_COLOR_PRESSED   0xFFE0u  // yellow
#define WASD_COLOR_UNPRESSED 0x2104u  // dark
#define WASD_COLOR_OUTLINE   0x7BEFu  // grey

#define MOUSE_BTN_RADIUS     30u
#define MOUSE_BTN_GAP        20u
#define MOUSE_BTN_Y          690u
#define MOUSE_BTN_RIGHT_X    (SCREEN_WIDTH - 60u)
#define MOUSE_BTN_LEFT_X     (MOUSE_BTN_RIGHT_X - 2 * MOUSE_BTN_RADIUS - MOUSE_BTN_GAP)
#define MOUSE_COLOR_PRESSED  0x07E0u  // green
#define MOUSE_COLOR_OUTLINE  0x7BEFu  // grey (same as WASD)

/* Centros (x) das 4 lanes, distribuídos pela metade esquerda (512px). */
static const uint16_t key_lane_cx[KEY_LANE_COUNT] = {64u, 192u, 320u, 448u};

static sprite_t *get_idle_frame(int frame_index) {
    static sprite_t *idle_sprites[FIGHTER_IDLE_FRAME_COUNT] = {0};

    if (frame_index < 0 || frame_index >= FIGHTER_IDLE_FRAME_COUNT)
        frame_index = 0;

    if (idle_sprites[frame_index] == NULL)
        idle_sprites[frame_index] = sprite_create(fighter_idle_frames[frame_index]);

    return idle_sprites[frame_index];
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

static font_t *get_hud_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(1);
        font_set_scale(font, 2);
    }

    return font;
}

static void draw_wasd_keys(const Game *g) {
    font_t *font = get_hud_font();
    if (font == NULL)
        return;

    static const char labels[4]  = {'W', 'A', 'S', 'D'};
    uint16_t kx[4], ky[4];
    kx[0] = WASD_X + WASD_KEY_SIZE + WASD_GAP;  ky[0] = WASD_Y;
    kx[1] = WASD_X;                              ky[1] = WASD_Y + WASD_KEY_SIZE + WASD_GAP;
    kx[2] = WASD_X + WASD_KEY_SIZE + WASD_GAP;  ky[2] = WASD_Y + WASD_KEY_SIZE + WASD_GAP;
    kx[3] = WASD_X + 2*(WASD_KEY_SIZE + WASD_GAP); ky[3] = WASD_Y + WASD_KEY_SIZE + WASD_GAP;

    for (int i = 0; i < 4; i++) {
        uint32_t fill = g->wasd_held[i] ? WASD_COLOR_PRESSED : WASD_COLOR_UNPRESSED;
        view_draw_rect(kx[i], ky[i], WASD_KEY_SIZE, WASD_KEY_SIZE, WASD_COLOR_OUTLINE);
        view_draw_rect(kx[i] + 2, ky[i] + 2, WASD_KEY_SIZE - 4, WASD_KEY_SIZE - 4, fill);

        char label[2] = {labels[i], '\0'};
        uint16_t lx = kx[i] + (WASD_KEY_SIZE - font_string_width(font, label)) / 2;
        uint16_t ly = ky[i] + (WASD_KEY_SIZE - font_line_height(font)) / 2;
        font_draw_string(font, label, lx, ly);
    }
}

static void draw_mouse_buttons(const Game *g) {
    font_t *font = get_hud_font();
    if (font == NULL)
        return;

    int cx[2] = { MOUSE_BTN_LEFT_X, MOUSE_BTN_RIGHT_X };
    const char *labels[2] = { "L", "R" };

    for (int i = 0; i < 2; i++) {
        int dx = g->mouse_x - cx[i];
        int dy = g->mouse_y - (int)MOUSE_BTN_Y;
        bool hovered = (dx * dx + dy * dy) <= (int)(MOUSE_BTN_RADIUS * MOUSE_BTN_RADIUS);
        view_draw_filled_circle(cx[i], MOUSE_BTN_Y, MOUSE_BTN_RADIUS, MOUSE_COLOR_OUTLINE);
        uint32_t fill = (hovered && g->mouse_held[0]) ? MOUSE_COLOR_PRESSED : WASD_COLOR_UNPRESSED;
        view_draw_filled_circle(cx[i], MOUSE_BTN_Y, MOUSE_BTN_RADIUS - 3, fill);

        uint16_t lx = cx[i] - font_string_width(font, labels[i]) / 2;
        uint16_t ly = MOUSE_BTN_Y - font_line_height(font) / 2;
        font_draw_string(font, labels[i], lx, ly);
    }
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

/* Alvos estáticos + tiles a cair (camada de frente). */
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

        int center_y = KEY_LANE_TOP;
        if (kp->response_window_ms > 0)
            center_y += travel * kp->elapsed_ms / kp->response_window_ms;
        if (center_y > KEY_HIT_ZONE_Y)
            center_y = KEY_HIT_ZONE_Y;

        sprite_t *tile = get_key_sprite(lane);
        if (tile != NULL)
            sprite_draw(tile, (uint16_t)(cx - tile->width / 2),
                        (uint16_t)(center_y - tile->height / 2));
    }
}

void active_view_draw(const Game *g) {
    uint32_t bg = (g->state == GS_ROUND_END) ? BG_COLOR_ROUND_END : BG_COLOR;
    view_draw_background(bg);
    sprite_draw(get_idle_frame(g->p1.anim_frame), FIGHTER_INSET, FIGHTER_Y);
    sprite_draw_mirrored(get_idle_frame(g->p2.anim_frame),
                         SCREEN_WIDTH - FIGHTER_INSET - FIGHTER_W, FIGHTER_Y);

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
    draw_wasd_keys(g);
    draw_mouse_buttons(g);
}
