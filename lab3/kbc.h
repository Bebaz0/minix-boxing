#ifndef _KBC_H_
#define _KBC_H_

#include <lcom/lcf.h>

/* Scancodes (make codes) */
#define SCANCODE_BREAK_MASK 0x80

#define SCANCODE_ESC        0x01
#define SCANCODE_ENTER      0x1C

#define SCANCODE_Q          0x10
#define SCANCODE_W          0x11
#define SCANCODE_E          0x12
#define SCANCODE_R          0x13
#define SCANCODE_A          0x1E
#define SCANCODE_S          0x1F
#define SCANCODE_D          0x20

#define SCANCODE_UP         0x48
#define SCANCODE_DOWN       0x50
#define SCANCODE_LEFT       0x4B
#define SCANCODE_RIGHT      0x4D


void (kbc_ih)();
int kbc_enable_int();

int kbc_subscribe_int(uint8_t *bit_no);
int kbc_unsubscribe_int();

/* Variáveis globais */
extern uint8_t scancode;
extern bool kbc_error;


#endif
