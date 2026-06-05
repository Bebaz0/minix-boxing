#include "name_input_controller.h"
#include "leaderboard.h"
#include "rtc.h"
#include "kbc.h"
#include "config.h"
#include <string.h>

#define SCANCODE_ENTER      0x1C
#define SCANCODE_BACKSPACE  0x0E
#define SCANCODE_BREAK_MASK 0x80

/* Maps make-code scancodes to uppercase characters for name entry. */
static char scancode_to_char(uint8_t sc) {
    switch (sc) {
        case 0x1E: return 'A'; case 0x30: return 'B'; case 0x2E: return 'C';
        case 0x20: return 'D'; case 0x12: return 'E'; case 0x21: return 'F';
        case 0x22: return 'G'; case 0x23: return 'H'; case 0x17: return 'I';
        case 0x24: return 'J'; case 0x25: return 'K'; case 0x26: return 'L';
        case 0x32: return 'M'; case 0x31: return 'N'; case 0x18: return 'O';
        case 0x19: return 'P'; case 0x10: return 'Q'; case 0x13: return 'R';
        case 0x1F: return 'S'; case 0x14: return 'T'; case 0x16: return 'U';
        case 0x2F: return 'V'; case 0x11: return 'W'; case 0x2D: return 'X';
        case 0x15: return 'Y'; case 0x2C: return 'Z';
        case 0x39: return ' ';
        default:   return '\0';
    }
}

void name_input_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;

    if (scancode & SCANCODE_BREAK_MASK)
        return;

    if (scancode == SCANCODE_BACKSPACE) {
        if (g->name_input_len > 0) {
            g->name_input_len--;
            g->name_input[g->name_input_len] = '\0';
        }
        return;
    }

    if (scancode == SCANCODE_ENTER) {
        if (g->name_input_len > 0) {
            LeaderboardEntry entry;
            memset(&entry, 0, sizeof(entry));
            memcpy(entry.name, g->name_input, (size_t)g->name_input_len);
            entry.name[g->name_input_len] = '\0';
            entry.winner           = g->winner;
            entry.match_duration_ms = g->match_elapsed_ms;
            rtc_read_date(&entry.date);

            leaderboard_add(&g->leaderboard, entry);
            leaderboard_save(&g->leaderboard, LEADERBOARD_FILE);
        }
        g->state          = GS_ROUND_END;
        g->state_timer_ms = INTER_ROUND_MS;
        return;
    }

    char ch = scancode_to_char(scancode);
    if (ch != '\0' && g->name_input_len < LEADERBOARD_NAME_LEN - 1) {
        g->name_input[g->name_input_len++] = ch;
        g->name_input[g->name_input_len]   = '\0';
    }
}
