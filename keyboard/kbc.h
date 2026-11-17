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


/**
 * @brief Keyboard interrupt handler.
 *
 * Reads the KBC status and, when the output buffer holds a valid byte, stores it
 * in the global ::scancode; on any error it sets ::kbc_error.
 */
void (kbc_ih)();
int kbc_enable_int();

/**
 * @brief Subscribes to keyboard interrupts in exclusive, reenable mode.
 *
 * @param bit_no Output parameter set to the bit of the assigned IRQ line
 * @return 0 on success, non-zero otherwise
 */
int kbc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes from keyboard interrupts.
 *
 * @return 0 on success, non-zero otherwise
 */
int kbc_unsubscribe_int();

/* Variáveis globais */
extern uint8_t scancode;
extern bool kbc_error;


#endif
