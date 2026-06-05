#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "config.h"
#include "player.h"
#include "key_prompt.h"
#include "bubble.h"
#include "menu.h"
#include "leaderboard.h"
#include "char_select.h"

typedef enum {
    GS_MENU,
    GS_ROUND_START,
    GS_ACTIVE,
    GS_PAUSE,
    GS_ROUND_END,
    GS_LEADERBOARD,
    GS_CHAR_SELECT,
    GS_INSTRUCTIONS,
    GS_QUIT
} GameState;

typedef struct Game {
    GameState  state;
    Player     p1;                               /* Jogador 1 — teclado */
    Player     p2;                               /* Jogador 2 — rato    */
    Menu       menu;
    CharSelect char_select;
    KeyPrompt  key_prompts[MAX_KEY_PROMPTS];     /* timing events do P1 */
    BubbleEvent bubbles[MAX_BUBBLES];            /* timing events do P2 */
    int        key_prompt_spawn_timer_ms;
    int        key_prompt_next_spawn_ms;        /* limiar aleatório para o próximo spawn */
    int        bubble_spawn_timer_ms;
    int        bubble_next_spawn_ms;            /* limiar aleatório para o próximo spawn */
    int        response_window_ms;               /* diminui por ronda   */
    int        round_elapsed_ms;
    int        round_duration_ms;
    int        state_timer_ms;                   /* conta ROUND_START / ROUND_END */
    int        menu_blink_timer_ms;              /* anima texto arcade no menu */
    int        round_number;                     /* começa em 1         */
    int        winner;                           /* 1, 2, ou 0 em empate */
    int        round_end_selected;               /* 0 = primary action, 1 = menu */
    int        pause_selected;                   /* 0 = RESUME,  1 = EXIT */
    bool       mouse_held[2];                    /* [0]=left [1]=right held state (visual feedback) */
    int        mouse_x, mouse_y;                 /* cursor position in screen coords */
    int        match_elapsed_ms;                 /* total match time, accumulates across rounds */
    Leaderboard leaderboard;
    char       name_input[LEADERBOARD_NAME_LEN];
    int        name_input_len;
    int        is_new_record;                    /* 1 while round-end panel is showing a record entry prompt */
} Game;

/**
 * @brief Initializes a game to its starting state.
 *
 * Zeroes the struct, loads the leaderboard from disk, initializes the menu and
 * both players, and leaves the game in the GS_MENU state.
 *
 * @param g Game to initialize
 */
void game_init(Game *g);

/**
 * @brief Resets per-round state and advances to the next round.
 *
 * Clears both players' round state, all key prompts and bubbles, increments the
 * round counter and transitions the game to GS_ROUND_START.
 *
 * @param g Game whose round is being reset
 */
void game_reset_round(Game *g);

/**
 * @brief Advances the game one logic tick.
 *
 * Drives the state machine: spawns/ticks timing events, resolves misses, updates
 * animations and timers, and detects round end (KO or time-up).
 *
 * @param g Game to update
 * @param delta_ms Elapsed time since the last update, in milliseconds
 */
void game_update(Game *g, int delta_ms);

/**
 * @brief Handles a Player 1 key press against the active key prompts.
 *
 * Matches the key to the most advanced active prompt and resolves the resulting
 * hit / perfect / miss outcome.
 *
 * @param g Game receiving the input
 * @param key Character of the key that was pressed
 */
void game_handle_key(Game *g, char key);

/**
 * @brief Handles a Player 2 mouse click against the active bubbles.
 *
 * @param g Game receiving the input
 * @param mx Cursor x coordinate, in screen pixels
 * @param my Cursor y coordinate, in screen pixels
 * @param button Mouse button that was pressed
 */
void game_handle_click(Game *g, int mx, int my, MouseButton button);

/**
 * @brief Checks whether the game has reached the quit state.
 *
 * @param g Game to query
 * @return true if the game state is GS_QUIT, false otherwise
 */
bool game_quit(const Game *g);

#endif /* GAME_H */
