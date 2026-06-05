#include "animation.h"
#include "../assets/fighters/fighter_types.h"

#define ANIM_FRAME_DURATION_MS 140

int animation_fighter_for_character(int char_idx) {
    return char_get_fighter_type(char_idx);
}

void animation_tick_player(Player *p, int fighter_type, int delta_ms) {
    p->anim_timer_ms += delta_ms;
    if (p->anim_timer_ms < ANIM_FRAME_DURATION_MS)
        return;

    p->anim_timer_ms -= ANIM_FRAME_DURATION_MS;

    if (p->anim == ANIM_SPECIAL || p->anim == ANIM_PUNCH || p->anim == ANIM_DEFENSE) {
        int count;
        if (p->anim == ANIM_SPECIAL)
            count = fighter_get_special_frame_count(fighter_type);
        else if (p->anim == ANIM_PUNCH)
            count = fighter_get_punch_frame_count(fighter_type);
        else
            count = fighter_get_defense_frame_count(fighter_type);

        if (count > 0) {
            p->anim_frame++;
            if (p->anim_frame >= count) {
                p->anim_frame = 0;
                p->anim = ANIM_IDLE;
            }
        } else {
            p->anim = ANIM_IDLE;
        }
    } else {
        int idle_count = fighter_get_idle_frame_count(fighter_type);
        p->anim_frame = (p->anim_frame + 1) % idle_count;
    }
}
