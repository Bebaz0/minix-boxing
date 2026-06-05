#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include <stdbool.h>

#include "i8042.h"


int (mouse_write_cmd)(uint8_t cmd);
int (mouse_disable_data_reporting)(void);

int (mouse_subscribe_interrupts)(uint8_t *bit_no);

int (mouse_unsubscribe_interrupts)();

void (mouse_ih)();

void (mouse_parse_packet)(uint8_t *packet_bytes, struct packet *p);

bool mouse_has_byte(void);
uint8_t get_mouse_byte();
#endif
