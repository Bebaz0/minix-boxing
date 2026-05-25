#include <lcom/lcf.h>
#include <minix/sysutil.h>

#include "timer.h"
#include "kbc.h"
#include "mouse.h"
#include "video.h"

#include "config.h"
#include "game.h"
#include "render.h"


int main(int argc, char *argv[]) {
    lcf_set_language("EN-US");

    if (lcf_start(argc, argv))
        return 1;


    uint8_t timer_bit, kbd_bit, mse_bit;

    if (timer_subscribe_int(&timer_bit) != 0) return 1;
    if (timer_set_frequency(0, TIMER_FREQ) != 0) return 1;
    if (kbc_subscribe_int(&kbd_bit) != 0) return 1;
    if (mouse_subscribe_interrupts(&mse_bit) != 0) return 1;

    int timer_irq = BIT(timer_bit);
    int kbd_irq   = BIT(kbd_bit);
    int mse_irq   = BIT(mse_bit);


    if (vg_init(VIDEO_MODE) == NULL) return 1;


    Game g;
    game_init(&g);


    uint8_t mse_buf[3];
    int     mse_idx = 0;


    int     ipc_status;
    message msg;

    while (!game_is_over(&g)) {

        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (!is_ipc_notify(ipc_status))
            continue;

        switch (_ENDPOINT_P(msg.m_source)) {

            case HARDWARE:
                if (msg.m_notify.interrupts & timer_irq) {
                    timer_int_handler();
                    game_update(&g, 1000 / TIMER_FREQ);
                    render_frame(&g);
                }

                if (msg.m_notify.interrupts & kbd_irq) {
                    kbc_ih();
                    if (!kbc_error) {
                        /* TODO: Converter scancode em carácter antes de passar ao jogo.
                           Por agora passa o byte diretamente — ajustar em game_handle_key. */
                        game_handle_key(&g, (char)scancode);
                    }
                }

                if (msg.m_notify.interrupts & mse_irq) {
                    mouse_ih();
                    mse_buf[mse_idx++] = get_mouse_byte();

                    if (mse_idx == 3) {
                        struct packet pkt;
                        mouse_parse_packet(mse_buf, &pkt);
                        mse_idx = 0;

                        /* TODO: Acumular o delta de posição (pkt.delta_x / pkt.delta_y)
                           e converter para coordenadas absolutas de ecrã antes de chamar
                           game_handle_click. Por agora passa (0,0) como valor provisório. */
                        if (pkt.lb)
                            game_handle_click(&g, 0, 0);
                    }
                }
                break;
        }
    }


    timer_unsubscribe_int();
    kbc_unsubscribe_int();
    mouse_unsubscribe_interrupts();

    vg_exit();

    lcf_cleanup();
    return 0;
}
