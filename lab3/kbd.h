#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"

extern uint32_t counter_KBC;

int (keyboard_subscribe_interrupts)(uint8_t *bit_no);

int (keyboard_unsubscribe_interrupts)();
#include "kbd.h"

uint8_t scancode = 0;
int kbd_hook_id = 1;
uint32_t counter_kbc = 0;

int (keyboard_subscribe_interrupts)(uint8_t *bit_no) {
    if (bit_no == NULL) return 1;
    *bit_no = BIT(kbd_hook_id);
    return sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id);
}

int (keyboard_unsubscribe_interrupts)() {
    return sys_irqrmpolicy(&kbd_hook_id);
}

void (kbc_ih)() {
    if (read_KBC_output(KBC_OUT_CMD, &scancode, 0) != 0) printf("Error: Could not read scancode!\n");
    counter_kbc++;
}

int (keyboard_restore)() {
    uint8_t commandByte;

    if (write_KBC_command(KBC_IN_CMD, KBC_READ_CMD) != 0) return 1;          
    if (read_KBC_output(KBC_OUT_CMD, &commandByte, 0) != 0) return 1; 

    commandByte |= ENABLE_INT;  

    if (write_KBC_command(KBC_IN_CMD, KBC_WRITE_CMD) != 0) return 1;    
    if (write_KBC_command(KBC_WRITE_CMD, commandByte) != 0) return 1;

    return 0;
}

void (kbc_ih)();

int (keyboard_restore)();

#endif
