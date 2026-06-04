#include "char_select_view.h"
#include "view_utils.h"
#include "sprites.h"
#include "font.h"
#include "config.h"
#include "../assets/fighter.h"

/* Panel centers */
#define CS_P1_CENTER_X    (SCREEN_WIDTH / 4)
#define CS_P2_CENTER_X    (3 * SCREEN_WIDTH / 4)
#define CS_PANEL_W        (SCREEN_WIDTH / 2)

/* Colors */
#define CS_COLOR_P1_PANEL   0x000Fu   /* dark blue  */
#define CS_COLOR_P2_PANEL   0x3800u   /* dark red   */
#define CS_COLOR_DIVIDER    0x7BEFu   /* grey       */
#define CS_COLOR_BOX_SEL    0xFFE0u   /* yellow     */
#define CS_COLOR_BOX_BORDER 0x4208u   /* dim border */
#define CS_COLOR_BOX_FILL   0x2104u   /* dark fill  */
#define CS_COLOR_BTN_READY  0x07E0u   /* green      */
#define CS_COLOR_BTN_WAIT   0x4208u   /* grey       */

/* Layout */
#define CS_LABEL_Y      20u
#define CS_FIGHTER_Y    80u
#define CS_HINT_Y      620u

static sprite_t *get_idle_frame(int frame_index) {
    static sprite_t *idle_sprites[FIGHTER_IDLE_FRAME_COUNT] = {0};

    if (frame_index < 0 || frame_index >= FIGHTER_IDLE_FRAME_COUNT)
        frame_index = 0;

    if (idle_sprites[frame_index] == NULL)
        idle_sprites[frame_index] = sprite_create(fighter_idle_frames[frame_index]);

    return idle_sprites[frame_index];
}

static font_t *get_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(1);
        font_set_scale(font, 2);
    }

    return font;
}

static void draw_char_boxes(uint16_t panel_left, int selected_char, sprite_t *char_sprite) {
    uint16_t total_w = CHAR_SELECT_COLS * CS_BOX_SIZE + (CHAR_SELECT_COLS - 1) * CS_BOX_GAP;
    uint16_t row_x = panel_left + (CS_PANEL_W - total_w) / 2;

    uint16_t inner = CS_BOX_SIZE - 5;
    int crop_x = (FIGHTER_W - inner) / 2;  /* centro horizontal do sprite */

    for (int i = 0; i < CHAR_COUNT; i++) {
        int col = i % CHAR_SELECT_COLS;
        int row = i / CHAR_SELECT_COLS;
        uint16_t bx = row_x + (uint16_t)col * (CS_BOX_SIZE + CS_BOX_GAP);
        uint16_t by = CS_BOX_Y + (uint16_t)row * (CS_BOX_SIZE + CS_BOX_GAP);
        uint32_t border = (i == selected_char) ? CS_COLOR_BOX_SEL : CS_COLOR_BOX_BORDER;

        view_draw_rect(bx, by, CS_BOX_SIZE, CS_BOX_SIZE, border);
        view_draw_rect(bx + 2, by + 2, inner, inner, CS_COLOR_BOX_FILL);

        if (char_sprite != NULL)
            sprite_draw_region(char_sprite, crop_x, 35, inner, inner, bx + 2, by + 2);
    }
}

static void draw_ready_button(uint16_t center_x, bool ready) {
    font_t *font = get_font();
    uint16_t bx = center_x - CS_BTN_W / 2;
    uint32_t color = ready ? CS_COLOR_BTN_READY : CS_COLOR_BTN_WAIT;

    view_draw_rect(bx, CS_BTN_Y, CS_BTN_W, CS_BTN_H, color);

    if (font == NULL) return;
    const char *label = "READY";
    uint16_t lx = center_x - font_string_width(font, label) / 2;
    uint16_t ly = CS_BTN_Y + (CS_BTN_H - font_line_height(font)) / 2;
    font_draw_string(font, label, lx, ly);
}

static void draw_centered_string(uint16_t center_x, uint16_t y, const char *text) {
    font_t *font = get_font();
    if (font == NULL) return;

    uint16_t lx = center_x - font_string_width(font, text) / 2;
    font_draw_string(font, text, lx, y);
}

void char_select_view_draw(const Game *g) {
    const CharSelect *cs = &g->char_select;

    view_draw_rect(0,          0, CS_PANEL_W, SCREEN_HEIGHT, CS_COLOR_P1_PANEL);
    view_draw_rect(CS_PANEL_W, 0, CS_PANEL_W, SCREEN_HEIGHT, CS_COLOR_P2_PANEL);

    view_draw_rect(CS_PANEL_W - 1, 0, 2, SCREEN_HEIGHT, CS_COLOR_DIVIDER);

    draw_centered_string(CS_P1_CENTER_X, CS_LABEL_Y, "PLAYER 1");
    draw_centered_string(CS_P2_CENTER_X, CS_LABEL_Y, "PLAYER 2");

    sprite_t *frame = get_idle_frame(g->p1.anim_frame);
    sprite_t *frame_p2 = get_idle_frame(g->p2.anim_frame);
    if (frame != NULL)
        sprite_draw(frame, CS_P1_CENTER_X - FIGHTER_W / 2, CS_FIGHTER_Y);
    if (frame_p2 != NULL)
        sprite_draw_mirrored(frame_p2, CS_P2_CENTER_X - FIGHTER_W / 2, CS_FIGHTER_Y);

    sprite_t *thumb = get_idle_frame(0);
    draw_char_boxes(0,          cs->p1_char, thumb);
    draw_char_boxes(CS_PANEL_W, cs->p2_char, thumb);

    draw_centered_string(CS_P1_CENTER_X, CS_HINT_Y, "ENTER");
    draw_centered_string(CS_P2_CENTER_X, CS_HINT_Y, "CLICK");

    draw_ready_button(CS_P1_CENTER_X, cs->p1_ready);
    draw_ready_button(CS_P2_CENTER_X, cs->p2_ready);
}
