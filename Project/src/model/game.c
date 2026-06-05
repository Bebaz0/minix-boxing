#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "animation.h"
#include "combat.h"
#include "leaderboard.h"
#include "rtc.h"

/* Inteiro aleatório em [lo, hi] usando os bits ALTOS do rand().
   Os bits baixos do rand() desta libc são fracos (ver comentário no spawn das
   bubbles), por isso rand() % n ficava enviesado — daí a divisão. */
static int key_tooltip_cx(char key) {
    static const int cx[4] = {KEY_LANE_CX_0, KEY_LANE_CX_1,
                               KEY_LANE_CX_2, KEY_LANE_CX_3};
    const char *keys = KEY_PROMPT_KEYS;
    int i;
    for (i = 0; i < KEY_LANE_COUNT; i++)
        if (keys[i] == key) return cx[i];
    return SCREEN_WIDTH / 2;
}

static void set_tooltip(Player *p, int type, int x, int y) {
    p->tooltip_type     = type;
    p->tooltip_timer_ms = TOOLTIP_DURATION_MS;
    p->tooltip_x        = x;
    p->tooltip_y        = y;
}

static int rand_range(int lo, int hi) {
    if (hi <= lo)
        return lo;
    int span = hi - lo + 1;
    return lo + rand() / (RAND_MAX / span + 1);
}

void game_init(Game *g) {
    memset(g, 0, sizeof(*g));
    leaderboard_load(&g->leaderboard, LEADERBOARD_FILE);
    menu_init(&g->menu);
    g->state              = GS_MENU;
    player_init(&g->p1);
    player_init(&g->p2);
    char_select_init(&g->char_select);
    g->response_window_ms = INITIAL_RESPONSE_WINDOW_MS;
    g->round_duration_ms  = ROUND_DURATION_MS;
    g->round_number       = 1;
    g->state_timer_ms     = ROUND_START_MS;
    g->state_timer_ms     = INTER_ROUND_MS;
    g->key_prompt_next_spawn_ms = rand_range(KEY_PROMPT_SPAWN_MIN_MS, KEY_PROMPT_SPAWN_MAX_MS);
    g->bubble_next_spawn_ms     = rand_range(BUBBLE_SPAWN_MIN_MS, BUBBLE_SPAWN_MAX_MS);
    g->mouse_x            = SCREEN_WIDTH / 2;
    g->mouse_y            = SCREEN_HEIGHT / 2;
}

void game_reset_round(Game *g) {
    player_reset_round_state(&g->p1);
    player_reset_round_state(&g->p2);
    memset(g->key_prompts, 0, sizeof(g->key_prompts));
    memset(g->bubbles, 0, sizeof(g->bubbles));
    g->key_prompt_spawn_timer_ms = 0;
    g->bubble_spawn_timer_ms     = 0;
    g->round_elapsed_ms          = 0;
    g->round_number++;
    g->round_end_selected        = 0;
    g->state                     = GS_ROUND_START;
    g->state_timer_ms            = ROUND_START_MS;
}

void game_update(Game *g, int delta_ms) {
    switch (g->state) {

        case GS_MENU:
            g->menu_blink_timer_ms += delta_ms;
            break;

        case GS_PAUSE:
        case GS_QUIT:
            break;

        case GS_CHAR_SELECT:
            animation_tick_player(&g->p1,
                                  animation_fighter_for_character(g->char_select.p1_char),
                                  delta_ms);
            animation_tick_player(&g->p2,
                                  animation_fighter_for_character(g->char_select.p2_char),
                                  delta_ms);
            if (char_select_both_ready(&g->char_select)) {
                g->state          = GS_ROUND_START;
                g->state_timer_ms = ROUND_START_MS;
            }
            break;

        case GS_ROUND_START:
            g->state_timer_ms -= delta_ms;
            if (g->state_timer_ms <= 0) {
                g->state                     = GS_ACTIVE;
                g->round_elapsed_ms          = 0;
                g->key_prompt_spawn_timer_ms = 0;
                g->key_prompt_next_spawn_ms  =
                    rand_range(KEY_PROMPT_SPAWN_MIN_MS, KEY_PROMPT_SPAWN_MAX_MS);
                g->bubble_spawn_timer_ms     = 0;
                g->bubble_next_spawn_ms      =
                    rand_range(BUBBLE_SPAWN_MIN_MS, BUBBLE_SPAWN_MAX_MS);
            }
            break;

        case GS_ACTIVE: {
            animation_tick_player(&g->p1,
                                  animation_fighter_for_character(g->char_select.p1_char),
                                  delta_ms);
            animation_tick_player(&g->p2,
                                  animation_fighter_for_character(g->char_select.p2_char),
                                  delta_ms);

            if (g->p1.tooltip_timer_ms > 0) g->p1.tooltip_timer_ms -= delta_ms;
            if (g->p2.tooltip_timer_ms > 0) g->p2.tooltip_timer_ms -= delta_ms;

            g->round_elapsed_ms  += delta_ms;
            g->match_elapsed_ms  += delta_ms;

            g->key_prompt_spawn_timer_ms += delta_ms;
            if (g->key_prompt_spawn_timer_ms >= g->key_prompt_next_spawn_ms) {
                g->key_prompt_spawn_timer_ms = 0;
                g->key_prompt_next_spawn_ms  =
                    rand_range(KEY_PROMPT_SPAWN_MIN_MS, KEY_PROMPT_SPAWN_MAX_MS);
                for (int i = 0; i < MAX_KEY_PROMPTS; i++) {
                    if (!g->key_prompts[i].active) {
                        char key = KEY_PROMPT_KEYS[rand_range(0, 3)];
                        key_prompt_spawn(&g->key_prompts[i], key, g->response_window_ms);
                        break;
                    }
                }
            }

            g->bubble_spawn_timer_ms += delta_ms;
            if (g->bubble_spawn_timer_ms >= g->bubble_next_spawn_ms) {
                g->bubble_spawn_timer_ms = 0;
                g->bubble_next_spawn_ms  =
                    rand_range(BUBBLE_SPAWN_MIN_MS, BUBBLE_SPAWN_MAX_MS);
                for (int i = 0; i < MAX_BUBBLES; i++) {
                    if (!g->bubbles[i].active) {
                        int x = rand_range(SCREEN_WIDTH / 2 + BUBBLE_RADIUS + 20, //+20 para não ficar muito perto do meio
                                            SCREEN_WIDTH - BUBBLE_RADIUS);
                        int y = rand_range(BUBBLE_RADIUS + 70, SCREEN_HEIGHT - BUBBLE_RADIUS - 50); //-20 para não ficar muito perto do chão
                        MouseButton btn = rand_range(0, 1) == 0 ? MOUSE_BUTTON_LEFT
                                                               : MOUSE_BUTTON_RIGHT;
                        bubble_spawn(&g->bubbles[i], x, y, BUBBLE_RADIUS, btn,
                                     g->response_window_ms);
                        break;
                    }
                }
            }

            for (int i = 0; i < MAX_KEY_PROMPTS; i++) {
                if (!g->key_prompts[i].active) continue;
                key_prompt_tick(&g->key_prompts[i], delta_ms);
                if (key_prompt_failed(&g->key_prompts[i])) {
                    combat_resolve(&g->p1, &g->p2, false, false);
                    set_tooltip(&g->p1, TOOLTIP_TYPE_MISS,
                                key_tooltip_cx(g->key_prompts[i].key),
                                KEY_HIT_ZONE_Y - KEY_TOOLTIP_Y_OFFSET);
                }
            }

            for (int i = 0; i < MAX_BUBBLES; i++) {
                if (!g->bubbles[i].active) continue;
                bubble_tick(&g->bubbles[i], delta_ms);
                if (bubble_failed(&g->bubbles[i])) {
                    combat_resolve(&g->p2, &g->p1, false, false);
                    set_tooltip(&g->p2, TOOLTIP_TYPE_MISS,
                                g->bubbles[i].x,
                                g->bubbles[i].y - g->bubbles[i].radius - 20);
                }
            }

            {
            bool p1_dead = player_is_dead(&g->p1);
            bool p2_dead = player_is_dead(&g->p2);
            bool time_up = (g->round_elapsed_ms >= g->round_duration_ms);

            if (p1_dead || p2_dead || time_up) {
                if      (p1_dead && p2_dead) g->winner = 0;
                else if (p1_dead)            g->winner = 2;
                else if (p2_dead)            g->winner = 1;
                else                         g->winner = 0;

                if (g->winner != 0 &&
                    leaderboard_is_record(&g->leaderboard, g->match_elapsed_ms)) {
                    memset(g->name_input, 0, sizeof(g->name_input));
                    g->name_input_len = 0;
                    g->is_new_record  = 1;
                }
                g->state          = GS_ROUND_END;
                g->state_timer_ms = INTER_ROUND_MS;
            }
            }
            break;
        }

        case GS_ROUND_END:
        case GS_LEADERBOARD:
        case GS_INSTRUCTIONS:
            break;
    }
}

void game_handle_key(Game *g, char key) {
    int best = -1;
    for (int i = 0; i < MAX_KEY_PROMPTS; i++) {
        if (!g->key_prompts[i].active || g->key_prompts[i].key != key)
            continue;
        if (best < 0 || g->key_prompts[i].elapsed_ms > g->key_prompts[best].elapsed_ms)
            best = i;
    }
    if (best >= 0 && key_prompt_press(&g->key_prompts[best], key)) {
        const KeyPrompt *kp = &g->key_prompts[best];
        bool landed = kp->hit || kp->perfect;
        combat_resolve(&g->p1, &g->p2, landed, kp->perfect);
        {
            int tt = !landed ? TOOLTIP_TYPE_MISS
                   : kp->perfect ? TOOLTIP_TYPE_PERFECT
                   : TOOLTIP_TYPE_HIT;
            set_tooltip(&g->p1, tt,
                        key_tooltip_cx(kp->key),
                        KEY_HIT_ZONE_Y - KEY_TOOLTIP_Y_OFFSET);
        }
    }
}

void game_handle_click(Game *g, int mx, int my, MouseButton button) {
    for (int i = 0; i < MAX_BUBBLES; i++) {
        if (!g->bubbles[i].active) continue;
        if (bubble_on_click(&g->bubbles[i], mx, my, button)) {
            int tt = g->bubbles[i].perfect ? TOOLTIP_TYPE_PERFECT : TOOLTIP_TYPE_HIT;
            combat_resolve(&g->p2, &g->p1, true, g->bubbles[i].perfect);
            set_tooltip(&g->p2, tt,
                        g->bubbles[i].x,
                        g->bubbles[i].y - g->bubbles[i].radius - 20);
            return;
        }
    }
}

bool game_quit(const Game *g) {
    return g->state == GS_QUIT;
}
