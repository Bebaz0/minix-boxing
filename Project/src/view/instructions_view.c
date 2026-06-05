#include "instructions_view.h"
#include "sprites.h"
#include "../assets/instructions_background.xpm"

static sprite_t *get_instructions_background_sprite(void) {
    static sprite_t *sprite = NULL;

    if (sprite == NULL)
        sprite = sprite_create(instructions_background_xpm);

    return sprite;
}

void instructions_view_draw(const Game *g) {
    (void)g;
    sprite_draw(get_instructions_background_sprite(), 0, 0);
}
