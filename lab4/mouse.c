#include "mouse.h"

static int mouse_hook_id = 12;

int (mouse_subscribe_interrupts)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = BIT(mouse_hook_id);
    return sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_interrupts)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}