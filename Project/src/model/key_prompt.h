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

void key_prompt_spawn(KeyPrompt *kp, char key, int response_window_ms);
bool key_prompt_press(KeyPrompt *kp, char key);   /* true se este prompt foi atingido */
void key_prompt_tick(KeyPrompt *kp, int delta_ms); /* desativa se o tempo expirar */
bool key_prompt_failed(const KeyPrompt *kp);       /* inativo por timeout, não por acerto */

#endif /* KEY_PROMPT_H */
