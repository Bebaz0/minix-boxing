#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <lcom/lcf.h>

extern uint8_t mouse_byte;
extern bool mouse_error;

int mouse_subscribe_int(uint8_t *bit_no);
int mouse_unsubscribe_int();

void (mouse_ih)();

int mouse_write_cmd(uint8_t cmd);
int mouse_disable_data_reporting();

void mouse_parse_packet(struct packet *pp);

#endif

