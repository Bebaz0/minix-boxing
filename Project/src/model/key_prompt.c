#include "key_prompt.h"

void key_prompt_spawn(KeyPrompt *kp, char key, int response_window_ms) {
    kp->key                = key;
    kp->response_window_ms = response_window_ms;
    kp->elapsed_ms         = 0;
    kp->active             = true;
    kp->hit                = false;
    kp->perfect            = false;
}

bool key_prompt_press(KeyPrompt *kp, char key) {
    if (!kp->active || kp->key != key)
        return false;

    /* O tile cai do topo da lane até ao alvo ao longo da janela e continua a cair (grace) 
    antes de desaparecer.*/
    int dist = kp->elapsed_ms - kp->response_window_ms;
    if (dist < 0)
        dist = -dist;
    int perfect_band = kp->response_window_ms * KEY_PERFECT_WINDOW_PCT / 100;
    int hit_band     = kp->response_window_ms * KEY_HIT_WINDOW_PCT / 100;

    if (dist <= perfect_band) {
        kp->perfect = true;
        kp->hit     = false;
    } else if (dist <= hit_band) {
        kp->perfect = false;
        kp->hit     = true;
    } else {
        /* Demasiado cedo ou já passou o alvo:*/
        kp->perfect = false;
        kp->hit     = false;
    }
    kp->active  = false;

    return true;
}

void key_prompt_tick(KeyPrompt *kp, int delta_ms) {
    if (!kp->active)
        return;

    kp->elapsed_ms += delta_ms;

    int despawn_ms = kp->response_window_ms * (100 + KEY_DESPAWN_EXTRA_PCT) / 100;
    if (kp->elapsed_ms >= despawn_ms)
        kp->active = false;
}

bool key_prompt_failed(const KeyPrompt *kp) {
    return !kp->active && !kp->hit && !kp->perfect;
}
