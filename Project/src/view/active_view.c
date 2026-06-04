#include <stdio.h>
#include "active_view.h"
#include "sprites.h"
#include "font.h"
#include "config.h"
#include "view_utils.h"
#include "../assets/fighter.h"

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

static sprite_t *get_idle_frame(int frame_index) {
    static sprite_t *idle_sprites[FIGHTER_IDLE_FRAME_COUNT] = {0};

    if (frame_index < 0 || frame_index >= FIGHTER_IDLE_FRAME_COUNT)
        frame_index = 0;

    if (idle_sprites[frame_index] == NULL)
        idle_sprites[frame_index] = sprite_create(fighter_idle_frames[frame_index]);

    return idle_sprites[frame_index];
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

void active_view_draw(const Game *g) {
    uint32_t bg = (g->state == GS_ROUND_END) ? BG_COLOR_ROUND_END : BG_COLOR;
    view_draw_background(bg);
    sprite_draw(get_idle_frame(g->p1.anim_frame), FIGHTER_INSET, FIGHTER_Y);
    sprite_draw_mirrored(get_idle_frame(g->p2.anim_frame),
                         SCREEN_WIDTH - FIGHTER_INSET - FIGHTER_W, FIGHTER_Y);
    draw_round_timer(g);
    draw_wasd_keys(g);
    draw_mouse_buttons(g);
}
