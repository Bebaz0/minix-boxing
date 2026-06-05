#include "instructions_view.h"
#include "sprites.h"
#include "font.h"
#include "config.h"
#include "../assets/instructions_background.xpm"

#define TEXT_WHITE  0xFFFFu
#define TEXT_YELLOW 0xFFE0u
#define TEXT_CYAN   0x07FFu
#define TEXT_RED    0xF800u
#define TEXT_GRAY   0xC618u

#define SECTION_X     120
#define GENERAL_Y     160
#define PLAYER1_Y     320
#define PLAYER2_Y     475
#define LINE_STEP      40
#define BACK_HINT_Y   655

static sprite_t *get_instructions_background_sprite(void) {
    static sprite_t *sprite = NULL;

    if (sprite == NULL)
        sprite = sprite_create(instructions_background_xpm);

    return sprite;
}

static font_t *get_body_font(void) {
    static font_t *font = NULL;

    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 2);
    }

    return font;
}

static void draw_section(font_t *font, const char *title,
                         const char *line1, const char *line2,
                         const char *line3,
                         uint16_t y, uint32_t title_color) {
    font_draw_string_color(font, title, SECTION_X, y, title_color);
    font_draw_string_color(font, line1, SECTION_X, y + LINE_STEP, TEXT_WHITE);
    font_draw_string_color(font, line2, SECTION_X, y + 2 * LINE_STEP, TEXT_WHITE);
    font_draw_string_color(font, line3, SECTION_X, y + 3 * LINE_STEP, TEXT_WHITE);
}

void instructions_view_draw(const Game *g) {
    (void)g;
    sprite_draw(get_instructions_background_sprite(), 0, 0);

    font_t *body_font = get_body_font();

    if (body_font == NULL)
        return;

    draw_section(body_font, "GENERAL",
                 "Choose your character and press READY",
                 "Both READY starts the round",
                 "Keep HP high and reduce the opponent HP",
                 GENERAL_Y, TEXT_YELLOW);

    draw_section(body_font, "PLAYER 1",
                 "Keyboard player",
                 "Press Q W E R when keys reach the target",
                 "Perfect timing builds combo",
                 PLAYER1_Y, TEXT_CYAN);

    draw_section(body_font, "PLAYER 2",
                 "Mouse player",
                 "Click bubbles with LEFT or RIGHT button",
                 "Match ring and bubble for perfect",
                 PLAYER2_Y, TEXT_RED);

    {
        const char *hint = "Press ESC to return";
        uint16_t hint_w = font_string_width(body_font, hint);
        font_draw_string_color(body_font, hint, (SCREEN_WIDTH - hint_w) / 2,
                               BACK_HINT_Y, TEXT_RED);
    }
}
