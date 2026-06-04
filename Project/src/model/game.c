#include <string.h>
#include <stdlib.h>
#include "game.h"
#include "combat.h"

#define ANIM_FRAME_DURATION_MS 120

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
                g->bubble_spawn_timer_ms     = 0;
            }
            break;

        case GS_ACTIVE: {
            tick_anim(&g->p1, delta_ms);
            tick_anim(&g->p2, delta_ms);

            g->round_elapsed_ms += delta_ms;

            g->key_prompt_spawn_timer_ms += delta_ms;
            if (g->key_prompt_spawn_timer_ms >= KEY_PROMPT_SPAWN_INTERVAL_MS) {
                g->key_prompt_spawn_timer_ms -= KEY_PROMPT_SPAWN_INTERVAL_MS;
                for (int i = 0; i < MAX_KEY_PROMPTS; i++) {
                    if (!g->key_prompts[i].active) {
                        char key = KEY_PROMPT_KEYS[rand() % 4];
                        key_prompt_spawn(&g->key_prompts[i], key, g->response_window_ms);
                        break;
                    }
                }
            }

            g->bubble_spawn_timer_ms += delta_ms;
            if (g->bubble_spawn_timer_ms >= BUBBLE_SPAWN_INTERVAL_MS) {
                g->bubble_spawn_timer_ms -= BUBBLE_SPAWN_INTERVAL_MS;
                for (int i = 0; i < MAX_BUBBLES; i++) {
                    if (!g->bubbles[i].active) {
                        int x = SCREEN_WIDTH / 2 + BUBBLE_RADIUS +
                                rand() % (SCREEN_WIDTH / 2 - 2 * BUBBLE_RADIUS);
                        int y = BUBBLE_RADIUS +
                                rand() % (SCREEN_HEIGHT - 2 * BUBBLE_RADIUS);
                        //Conta da Net porque usar só o rand estava a dar muito button left (algo a ver com os bits)
                        MouseButton btn = (rand() > RAND_MAX / 2) ? MOUSE_BUTTON_LEFT : MOUSE_BUTTON_RIGHT;
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
    for (int i = 0; i < MAX_KEY_PROMPTS; i++) {
        if (!g->key_prompts[i].active) continue;
        if (key_prompt_press(&g->key_prompts[i], key)) {
            combat_resolve(&g->p1, &g->p2, true, g->key_prompts[i].perfect);
            return;
        }
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
