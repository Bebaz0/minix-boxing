#include "active_view.h"
#include "sprites.h"
#include "config.h"
#include "view_utils.h"
#include "../assets/fighter.h"
#include "../assets/bubble_sprites.h"
#include "../assets/ring_sprites.h"

#define FIGHTER_Y     300u
#define FIGHTER_INSET 100u

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

void active_view_draw(const Game *g) {
    view_draw_background();
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
}
