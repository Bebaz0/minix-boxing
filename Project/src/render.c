#include "video.h"
#include "render.h"
#include "game.h"

void render_frame(const Game *g) {
    /* TODO: Limpar o ecrã (vg_draw_hline em toda a área com cor de fundo).

       Conforme g->state:

       GS_MENU
         — TODO: Desenhar ecrã de menu com opção de iniciar jogo.

       GS_ROUND_START
         — TODO: Desenhar contagem decrescente (3, 2, 1) antes do round começar.

       GS_ACTIVE
         — TODO: Desenhar fundo da arena.
         — TODO: Desenhar personagens (sprites de p1 e p2 conforme anim).
         — TODO: Percorrer g->arrows[]: desenhar cada slot com active==true.
         — TODO: Percorrer g->bubbles[]: desenhar cada slot com active==true.
         — TODO: Desenhar barras de HP de p1 e p2.
         — TODO: Desenhar barras de combo de p1 e p2.
         — TODO: Desenhar temporizador da ronda (round_elapsed_ms / round_duration_ms).

       GS_ROUND_END
         — TODO: Desenhar ecrã de pausa entre rondas com número da ronda seguinte.

       GS_GAME_OVER
         — TODO: Desenhar ecrã de fim de jogo com o vencedor (g->winner).
                 Opções: revanche ou sair. */
    (void)g;
}
