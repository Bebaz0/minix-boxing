#include "game_over_controller.h"
#include "leaderboard.h"
#include "rtc.h"
#include "kbc.h"
#include "config.h"
#include <string.h>

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

static int end_option_at(const Game *g, int x, int y) {
    int restart_y = g->is_new_record ? REC_RESTART_Y : END_RESTART_Y;
    int menu_y    = g->is_new_record ? REC_MENU_Y    : END_MENU_Y;

    if (x >= END_OPTION_X && x < END_OPTION_X + END_OPTION_W) {
        if (y >= restart_y && y < restart_y + END_OPTION_H) return 0;
        if (y >= menu_y    && y < menu_y    + END_OPTION_H) return 1;
    }
    return -1;
}

static void apply_end_selection(Game *g) {
    if (g->is_new_record && g->name_input_len > 0) {
        LeaderboardEntry entry;
        memset(&entry, 0, sizeof(entry));
        memcpy(entry.name, g->name_input, (size_t)g->name_input_len);
        entry.name[g->name_input_len] = '\0';
        entry.winner            = g->winner;
        entry.match_duration_ms = g->match_elapsed_ms;
        rtc_read_date(&entry.date);
        leaderboard_add(&g->leaderboard, entry);
        leaderboard_save(&g->leaderboard, LEADERBOARD_FILE);
    }
    g->is_new_record = 0;

    if (g->round_end_selected == 0) {
        if (g->winner == 0) {
            game_reset_round(g);
        } else {
            game_init(g);
            g->state = GS_CHAR_SELECT;
        }
    } else {
        game_init(g);
    }
}

void game_over_ctrl_handle_keyboard(Controller *ctrl, Game *g) {
    (void)ctrl;

    if (scancode & SCANCODE_BREAK_MASK)
        return;

    if (g->is_new_record == 1) {
        /* Typing name */
        if (scancode == SCANCODE_BACKSPACE) {
            if (g->name_input_len > 0) {
                g->name_input_len--;
                g->name_input[g->name_input_len] = '\0';
            }
            return;
        }
        if (scancode == SCANCODE_ENTER) {
            if (g->name_input_len > 0) {
                g->is_new_record = 2; /* confirm name, move to option selection */
                g->round_end_selected = 0;
            }
            return;
        }
        char ch = scancode_to_char(scancode);
        if (ch != '\0' && g->name_input_len < LEADERBOARD_NAME_LEN - 2) {
            g->name_input[g->name_input_len++] = ch;
            g->name_input[g->name_input_len]   = '\0';
        }
        return;
    }

    if (g->is_new_record == 2) {
        /* Name confirmed, selecting restart/menu */
        switch (scancode) {
            case SCANCODE_W:
            case SCANCODE_UP:
                g->round_end_selected = 0;
                break;
            case SCANCODE_S:
            case SCANCODE_DOWN:
                g->round_end_selected = 1;
                break;
            case SCANCODE_ENTER:
                apply_end_selection(g);
                break;
            default:
                break;
        }
        return;
    }

    switch (scancode) {
        case SCANCODE_W:
        case SCANCODE_UP:
            g->round_end_selected = 0;
            break;
        case SCANCODE_S:
        case SCANCODE_DOWN:
            g->round_end_selected = 1;
            break;
        case SCANCODE_ENTER:
            apply_end_selection(g);
            break;
        default:
            break;
    }
}

void game_over_ctrl_handle_mouse(Controller *ctrl, Game *g,
                                 bool left_clicked, bool right_clicked) {
    (void)right_clicked;

    int option = end_option_at(g, ctrl->mouse_x, ctrl->mouse_y);
    if (option >= 0)
        g->round_end_selected = option;

    if (left_clicked && option >= 0)
        apply_end_selection(g);
}
