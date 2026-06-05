#include "leaderboard_view.h"
#include "font.h"
#include "sprites.h"
#include "config.h"
#include "../assets/leaderboard_background.xpm"
#include <stdio.h>

static sprite_t *get_leaderboard_background_sprite(void) {
    static sprite_t *sprite = NULL;

    if (sprite == NULL)
        sprite = sprite_create(leaderboard_background_xpm);

    return sprite;
}

#define TEXT_WHITE  0xFFFFu
#define TEXT_YELLOW 0xFFE0u
#define TEXT_CYAN   0x07FFu
#define TEXT_GRAY   0xC618u
#define TEXT_RED    0xF800u

/* Column x positions */
#define COL_RANK    60
#define COL_NAME    160
#define COL_PLAYER  520
#define COL_TIME    680
#define COL_DATE    800

#define ROW_HEADER_Y 160
#define ROW_START_Y  220
#define ROW_STEP     46
#define BACK_HINT_Y  650

static font_t *get_table_font(void) {
    static font_t *font = NULL;
    if (font == NULL) {
        font = font_create_lcom(2);
        font_set_scale(font, 2);
    }
    return font;
}


void leaderboard_view_draw(const Game *g) {
    sprite_draw(get_leaderboard_background_sprite(), 0, 0);

    font_t *table_font = get_table_font();

    if (table_font == NULL)
        return;

    /* column headers */
    font_draw_string_color(table_font, "RANK",   COL_RANK,   ROW_HEADER_Y, TEXT_CYAN);
    font_draw_string_color(table_font, "NAME",   COL_NAME,   ROW_HEADER_Y, TEXT_CYAN);
    font_draw_string_color(table_font, "PLAYER", COL_PLAYER, ROW_HEADER_Y, TEXT_CYAN);
    font_draw_string_color(table_font, "TIME",   COL_TIME,   ROW_HEADER_Y, TEXT_CYAN);
    font_draw_string_color(table_font, "DATE",   COL_DATE,   ROW_HEADER_Y, TEXT_CYAN);

    if (g->leaderboard.count == 0) {
        const char *empty = "NO RECORDS YET";
        uint16_t ew = font_string_width(table_font, empty);
        font_draw_string_color(table_font, empty,
                               (SCREEN_WIDTH - ew) / 2, ROW_START_Y, TEXT_GRAY);
    } else {
        char buf[32];
        int count = g->leaderboard.count;
        if (count > LEADERBOARD_MAX_ENTRIES)
            count = LEADERBOARD_MAX_ENTRIES;

        for (int i = 0; i < count; i++) {
            const LeaderboardEntry *e = &g->leaderboard.entries[i];
            uint16_t row_y = (uint16_t)(ROW_START_Y + i * ROW_STEP);

            /* rank */
            snprintf(buf, sizeof(buf), "%d", i + 1);
            font_draw_string_color(table_font, buf, COL_RANK, row_y, TEXT_WHITE);

            /* name */
            font_draw_string_color(table_font, e->name, COL_NAME, row_y, TEXT_WHITE);

            /* player */
            snprintf(buf, sizeof(buf), "P%d", e->winner);
            font_draw_string_color(table_font, buf, COL_PLAYER, row_y, TEXT_WHITE);

            /* time in seconds */
            snprintf(buf, sizeof(buf), "%dS", e->match_duration_ms / 1000);
            font_draw_string_color(table_font, buf, COL_TIME, row_y, TEXT_WHITE);

            /* date DD MM YY */
            snprintf(buf, sizeof(buf), "%02u %02u %02u",
                     e->date.day, e->date.month, e->date.year);
            font_draw_string_color(table_font, buf, COL_DATE, row_y, TEXT_WHITE);
        }
    }

    {
        const char *hint = "PRESS ANY KEY TO RETURN";
        uint16_t hint_w = font_string_width(table_font, hint);
        font_draw_string_color(table_font, hint,
                               (SCREEN_WIDTH - hint_w) / 2,
                               BACK_HINT_Y,
                               TEXT_RED);
    }
}
