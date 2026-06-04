#include <lcom/lcf.h>
#include "mouse.h"
#include "kbc.h"
#include "i8042.h"
#include "kbc.h"

static int mouse_hook_id = 2;
static uint8_t mouse_byte;

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
    uint8_t status;
    if (util_sys_inb(KBC_STATUS_REG, &status) != 0) return;

    if (!(status & FULL_OUT_BUFFER)) return;

    uint8_t byte;
    if (util_sys_inb(KBC_OUT_CMD, &byte) != 0) return;

    if (status & BIT(5))   /* auxiliary (mouse) data */
        mouse_byte = byte;
}

void (mouse_parse_packet)(uint8_t *packet_bytes, struct packet *p) {
    for (int i = 0; i < 3; i++) {
        p->bytes[i] = packet_bytes[i];
    }

    p->lb = (packet_bytes[0] & BIT(0)); 
    p->rb = (packet_bytes[0] & BIT(1)); 
    p->mb = (packet_bytes[0] & BIT(2)); 

    p->x_ov = (packet_bytes[0] & BIT(6));
    p->y_ov = (packet_bytes[0] & BIT(7));

    if (packet_bytes[0] & BIT(4)) { 
        
        p->delta_x = 0xFF00 | packet_bytes[1];
    } else {
        p->delta_x = packet_bytes[1];
    }

    if (packet_bytes[0] & BIT(5)) {
        
        p->delta_y = 0xFF00 | packet_bytes[2];
    } else {
        p->delta_y = packet_bytes[2];
    }
}

uint8_t get_mouse_byte() {
    return mouse_byte;
}

