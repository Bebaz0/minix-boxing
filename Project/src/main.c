#include <lcom/lcf.h>
#include <minix/sysutil.h>

#include "timer.h"
#include "kbc.h"
#include "mouse.h"
#include "video.h"

#include "config.h"
#include "game.h"
#include "render.h"
#include "controller.h"

int main(int argc, char *argv[]) {
    lcf_set_language("EN-US");
    lcf_start(argc, argv);
    lcf_cleanup();
    return 0;
}

int(proj_main_loop)(int argc, char *argv[]) {
    (void)argc; (void)argv;

    uint8_t timer_bit, kbd_bit, mse_bit;

    if (timer_subscribe_int(&timer_bit) != 0) return 1;
    if (timer_set_frequency(0, TIMER_FREQ) != 0) return 1;
    if (kbc_subscribe_int(&kbd_bit) != 0) return 1;
    if (mouse_write_cmd(MOUSE_ENABLE_DATA) != 0) return 1;
    if (mouse_subscribe_interrupts(&mse_bit) != 0) return 1;

    int timer_irq = BIT(timer_bit);
    int kbd_irq   = BIT(kbd_bit);
    int mse_irq   = mse_bit;        /* mouse_subscribe_interrupts already returns BIT(hook_id) */

    if (vg_init(VIDEO_MODE) == NULL) return 1;

    Game g;
    Controller ctrl;

    game_init(&g);
    controller_init(&ctrl);

    int     ipc_status;
    message msg;
    int     timer_ms_remainder = 0;

    while (!game_quit(&g)) {

        if (driver_receive(ANY, &msg, &ipc_status) != 0)
            continue;

        if (!is_ipc_notify(ipc_status))
            continue;

        switch (_ENDPOINT_P(msg.m_source)) {

            case HARDWARE:
                if (msg.m_notify.interrupts & timer_irq) {
                    timer_int_handler();
                    timer_ms_remainder += 1000;
                    int delta_ms = timer_ms_remainder / TIMER_FREQ;
                    timer_ms_remainder %= TIMER_FREQ;
                    game_update(&g, delta_ms);
                    render_frame(&g);
                }

                if (msg.m_notify.interrupts & kbd_irq) {
                    kbc_ih();
                    controller_handle_keyboard(&ctrl, &g);
                }

                if (msg.m_notify.interrupts & mse_irq) {
                    mouse_ih();
                    controller_handle_mouse(&ctrl, &g);
                }
                break;
        }
    }

    mouse_disable_data_reporting();
    mouse_unsubscribe_interrupts();
    kbc_unsubscribe_int();
    timer_unsubscribe_int();

    vg_exit();
    return 0;
}
