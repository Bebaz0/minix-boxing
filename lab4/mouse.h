#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "i8042.h"
#include "kbc.h"


int (mouse_subscribe_interrupts)(uint8_t *bit_no);

int (mouse_unsubscribe_interrupts)();

void (mouse_ih)();

int (mouse_write_cmd)(uint8_t cmd);

uint8_t (mouse_get_byte)();

#endif
