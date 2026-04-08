#ifndef _KBC_H_
#define _KBC_H_

#include <lcom/lcf.h>

/* Interrupt handler */
void (kbc_ih)();

/* Subscribe / Unsubscribe interrupts */
int kbc_subscribe_int(uint8_t *bit_no);
int kbc_unsubscribe_int();

/* Variáveis globais */
extern uint8_t scancode;
extern bool kbc_error;

#endif
