#ifndef CONFIG_H
#define CONFIG_H

/* Ecrã */
#define SCREEN_WIDTH   1024
#define SCREEN_HEIGHT  768
#ifdef VIDEO_MODE
#undef VIDEO_MODE
#endif
#define VIDEO_MODE     0x117   /* 1024x768 16bpp cor direta */

/* Timer */
#ifdef TIMER_FREQ
#undef TIMER_FREQ
#endif
#define TIMER_FREQ     60      /* ticks por segundo */

/* Jogador */
#define PLAYER_MAX_HP       100
#define PLAYER_MAX_COMBO    100

/* TODO: Ajustar os valores de dano conforme o balanceamento do jogo */
#define NORMAL_DAMAGE       10
#define COMBO_DAMAGE        30

/* Duração de cada ronda (ms) — quando o contador chega a 0 a ronda termina */
/* TODO: Definir duração total de cada ronda */
#define ROUND_DURATION_MS             60000  /* 60 s safety net — match ends when someone dies */

/* Pausa entre rondas (ms) */
#define INTER_ROUND_MS                3000

/* TODO: Ajustar conforme o design do jogo */
#define MAX_KEY_PROMPTS  4   /* máximo de key prompts ativos ao mesmo tempo (Jogador 1) */
#define MAX_BUBBLES      4   /* máximo de bubbles ativas ao mesmo tempo (Jogador 2) */

/* Janela de resposta: tempo que o jogador tem para reagir a CADA timing event (ms).
   Podem existir vários eventos ativos ao mesmo tempo.
   Esta janela diminui a cada ronda, aumentando a dificuldade. */
/* TODO: Afinar os valores abaixo */
#define INITIAL_RESPONSE_WINDOW_MS    3000
#define RESPONSE_WINDOW_DECREASE_MS   200
#define MIN_RESPONSE_WINDOW_MS        500   /* limite mínimo para não chegar a 0 */

/* Intervalo entre spawn de novos timing events (ms) */
/* TODO: Definir ritmo de spawn e como varia com a dificuldade */
#define KEY_PROMPT_SPAWN_INTERVAL_MS  1500
#define BUBBLE_SPAWN_INTERVAL_MS      1500

/* Animação */
#define FIGHTER_IDLE_FRAME_COUNT  5   /* aumentar quando adicionar mais frames ao fighter.h */

/* Teclas do Jogador 1 */
#define KEY_PROMPT_KEYS "QWER"

/* Sensibilidade do Rato do Jogador 2 */
#define MOUSE_SENSITIVITY 2

/* Raio das bubbles (px) */
#define BUBBLE_RADIUS  40

/* Anel de aproximação (ring) das bubbles */
#define RING_START_SCALE_PCT    240  /* arranca a 2.4× o diâmetro da bubble */
#define RING_PERFECT_WINDOW_PCT  35  /* últimos 35% da janela: ring alinhado = perfect */

#endif /* CONFIG_H */
