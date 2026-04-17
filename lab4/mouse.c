#include "mouse.h"

static int mouse_hook_id = 12;

static uint8_t mouse_byte = 0;

uint8_t (mouse_get_byte)() {
    return mouse_byte;
}

int (mouse_subscribe_interrupts)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = BIT(mouse_hook_id);
    return sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_interrupts)() {
    return sys_irqrmpolicy(&mouse_hook_id);
}

int (mouse_write_cmd)(uint8_t cmd){
    uint8_t ack = 0xFE;
    while(ack == 0xFE){
        if(write_KBC_command(KBC_IN_CMD,MOUSE_WRITE_CMD) != 0) return -1;
        if(write_KBC_command(KBC_OUT_CMD, cmd) != 0) return -1;
        if(read_KBC_output(KBC_OUT_CMD, &ack, 1) != 0) return -1;
    }

    if(ack == 0xFC) return -1;
    
    return 0;
}

void (mouse_ih)(){
    if (read_KBC_output(KBC_OUT_CMD,&mouse_byte, 1) != 0) printf("Error: Could not read mouse get byte!\n");
}