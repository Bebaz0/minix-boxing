#ifndef KEY_PROMPT_H
#define KEY_PROMPT_H

#include <stdbool.h>
#include "config.h"

/* Um KeyPrompt é um timing event visual que mostra uma tecla (Q/W/E/R) no ecrã.
   O Jogador 1 tem de premir essa tecla antes da janela de resposta fechar. */
typedef struct {
    char key;               /* 'Q', 'W', 'E' ou 'R' */
    int  response_window_ms;
    int  elapsed_ms;
    bool active;            /* slot em uso */
    bool hit;               /* foi pressionado a tempo */
    bool perfect;           /* pressionado antes do threshold de perfeição */
} KeyPrompt;

/**
 * @brief Spawns (activates) a key-prompt timing event for a given key.
 *
 * @param kp Key prompt to initialize
 * @param key Character of the key the player must press
 * @param response_window_ms Time window during which the key can be hit
 */
void key_prompt_spawn(KeyPrompt *kp, char key, int response_window_ms);

/**
 * @brief Tests a key press against the prompt and records the outcome.
 *
 * If the key matches, deactivates the prompt and flags it as perfect, hit or
 * miss according to how close the press was to the target window.
 *
 * @param kp Key prompt being pressed
 * @param key Character of the key that was pressed
 * @return true if this prompt was hit by the press
 */
bool key_prompt_press(KeyPrompt *kp, char key);   /* true se este prompt foi atingido */

/**
 * @brief Advances the prompt's elapsed time and deactivates it on timeout.
 *
 * @param kp Key prompt to update
 * @param delta_ms Elapsed time since the last tick, in milliseconds
 */
void key_prompt_tick(KeyPrompt *kp, int delta_ms); /* desativa se o tempo expirar */

/**
 * @brief Checks whether the prompt expired without being hit.
 *
 * @param kp Key prompt to query
 * @return true if the prompt is inactive due to timeout (not a hit)
 */
bool key_prompt_failed(const KeyPrompt *kp);       /* inativo por timeout, não por acerto */

#endif /* KEY_PROMPT_H */
