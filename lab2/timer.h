#ifndef TIMER_H
#define TIMER_H

#include <lcom/lcf.h>
#include <stdint.h>

extern int counter;

/**
 * @brief Subscribes to Timer 0 interrupts in reenable mode.
 *
 * @param bit_no Output parameter set to the bit of the assigned IRQ line
 * @return 0 on success, non-zero otherwise
 */
int (timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes from Timer 0 interrupts.
 *
 * @return 0 on success, non-zero otherwise
 */
int (timer_unsubscribe_int)();

/**
 * @brief Timer 0 interrupt handler; increments the interrupt counter.
 */
void (timer_int_handler)();

int (timer_get_conf)(uint8_t timer, uint8_t *st);
int (timer_display_conf)(uint8_t timer, uint8_t conf, enum timer_status_field field);
/**
 * @brief Sets a timer's operating frequency.
 *
 * Uses the read-back command so the 4 LSBs (mode and BCD/binary) of the timer's
 * control word are preserved.
 *
 * @param timer Timer to configure (0 to 2)
 * @param freq Desired operating frequency, in Hz
 * @return 0 on success, non-zero otherwise
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq);

int (timer_get_counter)();
void (timer_set_counter)(int value);

#endif

