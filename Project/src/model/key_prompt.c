#include "key_prompt.h"

void key_prompt_spawn(KeyPrompt *kp, char key, int response_window_ms) {
    /* TODO*/
}

bool key_prompt_press(KeyPrompt *kp, char key) {
    /* TODO: Se kp->active e kp->key == key:
         kp->hit = true
         kp->perfect = (kp->elapsed_ms < kp->response_window_ms / 2)  -- TODO: afinar threshold
         kp->active = false
         devolver true.
       Caso contrário devolver false (tecla não corresponde a este slot). */
    return false;
}

void key_prompt_tick(KeyPrompt *kp, int delta_ms) {
    /* TODO: Se !kp->active, não fazer nada.
       Incrementar kp->elapsed_ms += delta_ms.
       Se elapsed_ms >= response_window_ms: kp->active = false (expirou sem ser pressionado). */
    (void)kp; (void)delta_ms;
}

bool key_prompt_failed(const KeyPrompt *kp) {
    /* TODO: Devolver true se !kp->active && !kp->hit
       (slot desativado por timeout, não por acerto). */
    (void)kp;
    return false;
}
