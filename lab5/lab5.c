#include <lcom/lcf.h>
#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>

#include "video.h"

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need it]
    lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab5/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
    reg86_t r;
    memset(&r, 0, sizeof(r));
    
    r.intno = 0x10;
    r.ax = 0x4F02;
    r.bx = mode | BIT(14);
  
    if (sys_int86(&r) != 0) return 1;
    
    sleep(delay);

    if (vg_exit() != 0) return 1;
    
    return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
    if (vg_init(mode) == NULL) {
        printf("%s: vg_init(0x%03X) failed\n", __func__, mode);
        return 1;
    }

    for (uint16_t row = 0; row < height; row++) {
        if (vg_draw_hline(x, y + row, width, color) != 0) {
            printf("%s: vg_draw_hline() failed\n", __func__);
            vg_exit();
            return 1;
        }
    }

    uint8_t bit_no = 1;
    int hook_id = bit_no;
    uint32_t irq_set = BIT(bit_no);

    if (sys_irqsetpolicy(1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0) {
        printf("%s: sys_irqsetpolicy() failed\n", __func__);
        vg_exit();
        return 1;
    }

    int ipc_status, r;
    message msg;
    bool done = false;

    while (!done) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d\n", r);
            continue;
        }

        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            if (msg.m_notify.interrupts & irq_set) {
                uint32_t status, data;
                if (sys_inb(0x64, &status) == 0 && (status & BIT(0))) {
                    if (sys_inb(0x60, &data) == 0 && (status & (BIT(7) | BIT(6))) == 0) {
                        if (data == 0x81) {
                            done = true;
                        }
                    }
                }
            }
        }
    }

    if (sys_irqrmpolicy(&hook_id) != 0) {
        printf("%s: sys_irqrmpolicy() failed\n", __func__);
    }

    if (vg_exit() != 0) {
        printf("%s: vg_exit() failed\n", __func__);
        return 1;
    }

    return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  if (vg_init(0x105) == NULL) return 1;

  if (draw_xpm(x, y, xpm) != 0) return 1;

  sleep(5);

  vg_exit();

  return 0;
}