#include "mouse.h"

int mouse_hook_id = 12;
uint8_t mouse_byte;

int (mouse_subscribe_interrupts)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = BIT(mouse_hook_id);
    return sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_interrupts)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}
int (mouse_write_cmd)(uint8_t cmd) {
    uint8_t ack;
    
    if (write_KBC_command(KBC_STATUS_REG, KBC_WRITE_TO_MOUSE) != 0) return 1;

    if (write_KBC_command(KBC_OUT_CMD, cmd) != 0) return 1;

    if (read_KBC_output(KBC_OUT_CMD, &ack, 1) != 0) return 1;

    return (ack == MOUSE_ACK) ? 0 : 1; 
}

void (mouse_ih)() {
    if (util_sys_inb(KBC_OUT_CMD, &mouse_byte) != 0) {
        printf("Erro ao ler byte do rato!\n");
    }
}