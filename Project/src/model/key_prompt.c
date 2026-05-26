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

    kp->hit     = true;
    kp->perfect = kp->elapsed_ms < kp->response_window_ms / 2;
    kp->active  = false;

    return true;
}

void key_prompt_tick(KeyPrompt *kp, int delta_ms) {
    if (!kp->active)
        return;

    kp->elapsed_ms += delta_ms;

    if (kp->elapsed_ms >= kp->response_window_ms)
        kp->active = false;
}

bool key_prompt_failed(const KeyPrompt *kp) {
    return !kp->active && !kp->hit;
}
