#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include <stdbool.h>

#include "i8042.h"


/**
 * @brief Writes a command byte to the mouse and checks its acknowledgement.
 *
 * @param cmd Command byte to send to the mouse
 * @return 0 if the mouse acknowledged the command, non-zero otherwise
 */
int (mouse_write_cmd)(uint8_t cmd);

/**
 * @brief Disables mouse data reporting (stops streaming movement packets).
 *
 * @return 0 on success, non-zero otherwise
 */
int (mouse_disable_data_reporting)(void);

/**
 * @brief Subscribes to mouse interrupts in exclusive, reenable mode.
 *
 * @param bit_no Output parameter set to the bitmask of the assigned IRQ line
 * @return 0 on success, non-zero otherwise
 */
int (mouse_subscribe_interrupts)(uint8_t *bit_no);

/**
 * @brief Unsubscribes from mouse interrupts.
 *
 * @return 0 on success, non-zero otherwise
 */
int (mouse_unsubscribe_interrupts)();

/**
 * @brief Mouse interrupt handler.
 *
 * Reads one byte from the KBC output buffer when it holds valid mouse data and
 * stores it for later retrieval.
 */
void (mouse_ih)();

/**
 * @brief Parses a raw 3-byte mouse packet into a structured packet.
 *
 * @param packet_bytes Array of the 3 raw packet bytes
 * @param p Output packet filled with button state, deltas and overflow flags
 */
void (mouse_parse_packet)(uint8_t *packet_bytes, struct packet *p);

/**
 * @brief Checks whether a mouse byte read by the handler is pending.
 *
 * @return true if a byte is available to be consumed
 */
bool mouse_has_byte(void);

/**
 * @brief Consumes and returns the byte stored by the interrupt handler.
 *
 * Clears the pending flag so the same byte is not read twice.
 *
 * @return The most recently received mouse byte
 */
uint8_t get_mouse_byte();
#endif
