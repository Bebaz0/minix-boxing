#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "combat.h"

#define ANIM_FRAME_DURATION_MS 120

/* Inteiro aleatório em [lo, hi] usando os bits ALTOS do rand().
   Os bits baixos do rand() desta libc são fracos (ver comentário no spawn das
   bubbles), por isso rand() % n ficava enviesado — daí a divisão. */
static int rand_range(int lo, int hi) {
    if (hi <= lo)
        return lo;
    int span = hi - lo + 1;
    return lo + rand() / (RAND_MAX / span + 1);
}

static void tick_anim(Player *p, int delta_ms) {
    p->anim_timer_ms += delta_ms;
    if (p->anim_timer_ms >= ANIM_FRAME_DURATION_MS) {
        p->anim_timer_ms -= ANIM_FRAME_DURATION_MS;
        p->anim_frame = (p->anim_frame + 1) % FIGHTER_IDLE_FRAME_COUNT;
    }
}

void game_init(Game *g) {
    memset(g, 0, sizeof(*g));
    menu_init(&g->menu);
    g->state              = GS_MENU;
    player_init(&g->p1);
    player_init(&g->p2);
    g->response_window_ms = INITIAL_RESPONSE_WINDOW_MS;
    g->round_duration_ms  = ROUND_DURATION_MS;
    g->round_number       = 1;
    g->state_timer_ms     = INTER_ROUND_MS;
    g->key_prompt_next_spawn_ms = rand_range(KEY_PROMPT_SPAWN_MIN_MS, KEY_PROMPT_SPAWN_MAX_MS);
    g->bubble_next_spawn_ms     = rand_range(BUBBLE_SPAWN_MIN_MS, BUBBLE_SPAWN_MAX_MS);
    g->mouse_x            = SCREEN_WIDTH / 2;
    g->mouse_y            = SCREEN_HEIGHT / 2;
}

void game_reset_round(Game *g) {
    player_init(&g->p1);
    player_init(&g->p2);
    memset(g->key_prompts, 0, sizeof(g->key_prompts));
    memset(g->bubbles, 0, sizeof(g->bubbles));
    g->key_prompt_spawn_timer_ms = 0;
    g->bubble_spawn_timer_ms     = 0;
    g->round_elapsed_ms          = 0;
    g->round_number++;
    g->round_end_selected        = 0;
    g->state                     = GS_ROUND_START;
    g->state_timer_ms            = INTER_ROUND_MS;
}

void game_update(Game *g, int delta_ms) {
    switch (g->state) {

        case GS_MENU:
        case GS_PAUSE:
        case GS_QUIT:
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
            tick_anim(&g->p1, delta_ms);
            tick_anim(&g->p2, delta_ms);

            g->round_elapsed_ms += delta_ms;

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
                        int x = rand_range(SCREEN_WIDTH / 2 + BUBBLE_RADIUS,
                                           SCREEN_WIDTH - BUBBLE_RADIUS);
                        int y = rand_range(BUBBLE_RADIUS, SCREEN_HEIGHT - BUBBLE_RADIUS);
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
                if (key_prompt_failed(&g->key_prompts[i]))
                    combat_resolve(&g->p1, &g->p2, false, false);
            }

            for (int i = 0; i < MAX_BUBBLES; i++) {
                if (!g->bubbles[i].active) continue;
                bubble_tick(&g->bubbles[i], delta_ms);
                if (bubble_failed(&g->bubbles[i]))
                    combat_resolve(&g->p2, &g->p1, false, false);
            }

            {
            bool p1_dead = player_is_dead(&g->p1);
            bool p2_dead = player_is_dead(&g->p2);
            bool time_up = (g->round_elapsed_ms >= g->round_duration_ms);

            if (p1_dead || p2_dead || time_up) {
                if      (p1_dead && p2_dead) g->winner = 0;
                else if (p1_dead)            g->winner = 2;
                else if (p2_dead)            g->winner = 1;
                else                         g->winner = (g->p1.hp >= g->p2.hp) ? 1 : 2;

                g->state          = GS_ROUND_END;
                g->state_timer_ms = INTER_ROUND_MS;
            }
            }
            break;
        }

        case GS_ROUND_END:
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
    }
}

void game_handle_click(Game *g, int mx, int my, MouseButton button) {
    for (int i = 0; i < MAX_BUBBLES; i++) {
        if (!g->bubbles[i].active) continue;
        if (bubble_on_click(&g->bubbles[i], mx, my, button)) {
            combat_resolve(&g->p2, &g->p1, true, g->bubbles[i].perfect);
            return;
        }
    }
}

bool game_quit(const Game *g) {
    return g->state == GS_QUIT;
}
