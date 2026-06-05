#ifndef FIGHTER_SPRITES_H
#define FIGHTER_SPRITES_H

#include "sprites.h"
#include "../assets/fighter_types.h"

/* Retorna o sprite idle (cache partilhada) para o tipo e frame dados.
   Nunca retorna um valor sem verificar NULL — sprite_create pode falhar. */
sprite_t *fighter_get_idle_sprite(int fighter_type, int frame_index);

#endif /* FIGHTER_SPRITES_H */
