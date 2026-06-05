#include "char_select_view.h"
#include "view_utils.h"
#include "sprites.h"
#include "font.h"
#include "config.h"
#include "fighter_sprites.h"
#include "video.h"

/* Panel centers */
#define CS_P1_CENTER_X    (SCREEN_WIDTH / 4)
#define CS_P2_CENTER_X    (3 * SCREEN_WIDTH / 4)
#define CS_PANEL_W        (SCREEN_WIDTH / 2)

/* Panel background colors */
#define CS_COLOR_P1_PANEL   0x000Fu   /* dark blue  */
#define CS_COLOR_P2_PANEL   0x3800u   /* dark red   */
#define CS_COLOR_DIVIDER    0x7BEFu   /* grey       */

/* Box border / fill colors */
#define CS_COLOR_BOX_SEL    0xFFE0u   /* yellow  — selected   */
#define CS_COLOR_BOX_BORDER 0x4208u   /* border               */
#define CS_COLOR_BOX_FILL   0x2104u   /* dark fill — default  */

/* Ready-button colors */
#define CS_COLOR_BTN_READY  0x07E0u   /* green      */
#define CS_COLOR_BTN_WAIT   0x4208u   /* grey       */

/* Layout */
#define CS_LABEL_Y      20u
#define CS_FIGHTER_Y    80u
#define CS_HINT_Y      620u


static font_t *get_font(void) {
    static font_t *font = NULL;
    if (font == NULL) {
        font = font_create_lcom(1);
        font_set_scale(font, 2);
    }
    return font;
}

static void draw_centered_string(uint16_t center_x, uint16_t y, const char *text) {
    font_t *font = get_font();
    if (font == NULL) return;
    uint16_t lx = center_x - font_string_width(font, text) / 2;
    font_draw_string(font, text, lx, y);
}


static void draw_char_head(const sprite_t *s, int dst_x, int dst_y,
                           int dst_size, int src_size, int crop_y_pct, int x_shift) {
    uint16_t *pixels = (uint16_t *)s->pixels;
    int crop_y = (int)s->height * crop_y_pct / 100;
    int crop_x = ((int)s->width  - src_size) / 2 - x_shift;
    if (crop_x < 0) crop_x = 0;

    for (int row = 0; row < dst_size; row++) {
        int sy = crop_y + src_size * row / dst_size;
        if (sy >= (int)s->height) continue;
        for (int col = 0; col < dst_size; col++) {
            int sx = crop_x + src_size * col / dst_size;
            if (sx >= (int)s->width) continue;
            uint32_t color = pixels[sy * s->width + sx];
            if (color == s->transparent_color) continue;
            vg_draw_pixel((uint16_t)(dst_x + col), (uint16_t)(dst_y + row), color);
        }
    }
}

static void draw_char_boxes(uint16_t panel_left, int selected_char) {
    uint16_t total_w = CHAR_SELECT_COLS * CS_BOX_SIZE + (CHAR_SELECT_COLS - 1) * CS_BOX_GAP;
    uint16_t row_x   = panel_left + (CS_PANEL_W - total_w) / 2;
    uint16_t inner   = CS_BOX_SIZE - 5;

    for (int i = 0; i < CHAR_COUNT; i++) {
        int      col    = i % CHAR_SELECT_COLS;
        int      row    = i / CHAR_SELECT_COLS;
        uint16_t bx     = row_x + (uint16_t)col * (CS_BOX_SIZE + CS_BOX_GAP);
        uint16_t by     = CS_BOX_Y + (uint16_t)row * (CS_BOX_SIZE + CS_BOX_GAP);
        uint32_t border = (i == selected_char) ? CS_COLOR_BOX_SEL : CS_COLOR_BOX_BORDER;
        uint32_t fill   = CS_COLOR_BOX_FILL;

        view_draw_rect(bx,     by,     CS_BOX_SIZE, CS_BOX_SIZE, border);
        view_draw_rect(bx + 2, by + 2, inner,       inner,       fill);

        int ft = char_fighter_type[i];
        sprite_t *thumb = fighter_get_idle_sprite(ft, 0);
        if (thumb == NULL) continue;

        /* src_size maior = menos zoom (mostra mais pixels do sprite na caixa).
           crop_y_pct: altura do sprite onde começa o corte, em percentagem.
           x_shift: move o conteúdo para a direita (+) ou esquerda (-). */
        int src_size, crop_y_pct, x_shift;
        switch (ft) {
            case FIGHTER_TYPE_GOKU:   src_size = 100; crop_y_pct = 20; x_shift = -45; break;
            case FIGHTER_TYPE_VEGETA: src_size =  90; crop_y_pct = 22; x_shift =   0; break;
            case FIGHTER_TYPE_MARIO:  src_size =  25; crop_y_pct =  5; x_shift =   0; break;
            case FIGHTER_TYPE_SONIC:  src_size =  20; crop_y_pct =  18; x_shift =   -10; break;
            default:                  src_size =  70; crop_y_pct =  8; x_shift =   5; break;
        }
        draw_char_head(thumb, bx + 2, by + 2, (int)inner, src_size, crop_y_pct, x_shift);
    }
}

static void draw_fighter_preview(uint16_t panel_left, uint16_t center_x,
                                 int fighter_type, int anim_frame, bool mirrored) {
    sprite_t *frame = fighter_get_idle_sprite(fighter_type, anim_frame);

    if (frame != NULL) {
        int w = fighter_w(fighter_type), h = fighter_h(fighter_type);
        int draw_x = (int)center_x - w / 2;
        int draw_y = CS_FIGHTER_Y + FIGHTER_H_PX - h;  
        if (mirrored)
            sprite_draw_to_size_mirrored(frame, draw_x, draw_y, w, h);
        else
            sprite_draw_to_size(frame, draw_x, draw_y, w, h);
    }
}

static void draw_ready_button(uint16_t center_x, bool ready) {
    font_t  *font  = get_font();
    uint16_t bx    = center_x - CS_BTN_W / 2;
    uint32_t color = ready ? CS_COLOR_BTN_READY : CS_COLOR_BTN_WAIT;

    view_draw_rect(bx, CS_BTN_Y, CS_BTN_W, CS_BTN_H, color);

    if (font == NULL) return;
    const char *label = "READY";
    uint16_t lx = center_x - font_string_width(font, label) / 2;
    uint16_t ly = CS_BTN_Y + (CS_BTN_H - font_line_height(font)) / 2;
    font_draw_string(font, label, lx, ly);
}

void char_select_view_draw(const Game *g) {
    const CharSelect *cs = &g->char_select;

    view_draw_rect(0, 0, CS_PANEL_W, SCREEN_HEIGHT, CS_COLOR_P1_PANEL);
    view_draw_rect(CS_PANEL_W, 0, CS_PANEL_W, SCREEN_HEIGHT, CS_COLOR_P2_PANEL);
    view_draw_rect(CS_PANEL_W - 1, 0, 2, SCREEN_HEIGHT, CS_COLOR_DIVIDER);

    draw_centered_string(CS_P1_CENTER_X, CS_LABEL_Y, "PLAYER 1");
    draw_centered_string(CS_P2_CENTER_X, CS_LABEL_Y, "PLAYER 2");

    int ft1 = char_get_fighter_type(cs->p1_char);
    int ft2 = char_get_fighter_type(cs->p2_char);
    draw_fighter_preview(0, CS_P1_CENTER_X, ft1, g->p1.anim_frame, false);
    draw_fighter_preview(CS_PANEL_W, CS_P2_CENTER_X, ft2, g->p2.anim_frame, true);

    draw_char_boxes(0, cs->p1_char);
    draw_char_boxes(CS_PANEL_W, cs->p2_char);

    draw_centered_string(CS_P1_CENTER_X, CS_HINT_Y, "ENTER");
    draw_centered_string(CS_P2_CENTER_X, CS_HINT_Y, "CLICK");
    draw_ready_button(CS_P1_CENTER_X, cs->p1_ready);
    draw_ready_button(CS_P2_CENTER_X, cs->p2_ready);
}
