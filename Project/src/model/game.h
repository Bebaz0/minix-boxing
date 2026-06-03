#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "config.h"
#include "player.h"
#include "key_prompt.h"
#include "bubble.h"
#include "menu.h"

typedef enum {
    GS_MENU,
    GS_ROUND_START,
    GS_ACTIVE,
    GS_PAUSE,
    GS_ROUND_END,
    GS_QUIT
} GameState;

typedef struct Game {
    GameState  state;
    Player     p1;                               /* Jogador 1 — teclado */
    Player     p2;                               /* Jogador 2 — rato    */
    Menu       menu;
    KeyPrompt  key_prompts[MAX_KEY_PROMPTS];     /* timing events do P1 */
    BubbleEvent bubbles[MAX_BUBBLES];            /* timing events do P2 */
    int        key_prompt_spawn_timer_ms;
    int        bubble_spawn_timer_ms;
    int        response_window_ms;               /* diminui por ronda   */
    int        round_elapsed_ms;
    int        round_duration_ms;
    int        state_timer_ms;                   /* conta ROUND_START / ROUND_END */
    int        round_number;                     /* começa em 1         */
    int        winner;                           /* 1, 2, ou 0 em empate */
    int        round_end_selected;               /* 0 = RESTART, 1 = MENU */
    int        pause_selected;                   /* 0 = RESUME,  1 = EXIT */
    bool       wasd_held[4];                     /* W A S D held state (visual feedback) */
} Game;

void game_init(Game *g);
void game_reset_round(Game *g);
void game_update(Game *g, int delta_ms);
void game_handle_key(Game *g, char key);
void game_handle_click(Game *g, int mx, int my, MouseButton button);
bool game_quit(const Game *g);

#endif /* GAME_H */
