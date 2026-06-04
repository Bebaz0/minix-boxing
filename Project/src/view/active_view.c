#include <stdio.h>
#include "active_view.h"
#include "sprites.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"
#include "../assets/fighter.h"
#include "../assets/bubble_sprites.h"
#include "../assets/ring_sprites.h"
#include "../assets/game_background.xpm"

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

static sprite_t *get_idle_frame(int frame_index) {
    static sprite_t *idle_sprites[FIGHTER_IDLE_FRAME_COUNT] = {0};

    if (frame_index < 0 || frame_index >= FIGHTER_IDLE_FRAME_COUNT)
        frame_index = 0;

    if (idle_sprites[frame_index] == NULL)
        idle_sprites[frame_index] = sprite_create(fighter_idle_frames[frame_index]);

    return idle_sprites[frame_index];
}

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
            bubble_left = sprite_create((xpm_map_t)bubble_L_xpm);
        return bubble_left;
    }
    if (bubble_right == NULL)
        bubble_right = sprite_create((xpm_map_t)bubble_R_xpm);
    return bubble_right;
}

static sprite_t *get_ring_sprite(MouseButton btn) {
    static sprite_t *ring_left  = NULL;
    static sprite_t *ring_right = NULL;

    if (btn == MOUSE_BUTTON_LEFT) {
        if (ring_left == NULL)
            ring_left = sprite_create((xpm_map_t)ring_L_xpm);
        return ring_left;
    }
    if (ring_right == NULL)
        ring_right = sprite_create((xpm_map_t)ring_R_xpm);
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

void active_view_draw(const Game *g) {
    active_view_draw_background();

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
    draw_round_timer(g);
    draw_wasd_keys(g);
}
