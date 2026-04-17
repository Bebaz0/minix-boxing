#ifndef _I8042_H_
#define _I8042_H_

#include <lcom/lcf.h>

/* IRQs */
#define KBC_IRQ   1
#define MOUSE_IRQ 12

/* KBC ports */
#define KBC_OUT_BUF 0x60
#define KBC_IN_BUF  0x60
#define KBC_ST_REG  0x64
#define KBC_CMD_REG 0x64

/* Status Register bits */
#define KBC_OBF     BIT(0)
#define KBC_IBF     BIT(1)
#define KBC_AUX     BIT(5)
#define KBC_TO_ERR  BIT(6)
#define KBC_PAR_ERR BIT(7)

/* Keyboard Scancodes */
#define ESC_BREAK_CODE 0x81
#define TWO_BYTE_CODE  0xE0

/* KBC Commands */
#define KBC_READ_CMD   0x20
#define KBC_WRITE_CMD  0x60

/* KBC Command Byte bits */
#define KBC_INT BIT(0)

/* Mouse Commands (via KBC) */
#define WRITE_TO_MOUSE 0xD4

/* Mouse Commands */
#define ENABLE_DATA_REPORTING  0xF4
#define DISABLE_DATA_REPORTING 0xF5

/* Mouse Responses */
#define ACK   0xFA
#define NACK  0xFE
#define ERROR 0xFC

#endif