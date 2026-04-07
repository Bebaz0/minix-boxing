#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int hook_id = 0;
uint32_t counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (freq > TIMER_FREQ || freq < 19) return 1;

  uint8_t controlWord;
  if (timer_get_conf(timer, &controlWord) != 0) return 1;

  controlWord = (controlWord & 0x0F) | TIMER_LSB_MSB; 

  uint32_t initialValue = TIMER_FREQ / freq;
  uint8_t MSB, LSB;
  util_get_MSB(initialValue, &MSB);
  util_get_LSB(initialValue, &LSB);

  uint8_t selectedTimer;      
  switch (timer) {  
    case 0: 
      controlWord |= TIMER_SEL0;
      selectedTimer = TIMER_0;
      break;
    case 1:
      controlWord |= TIMER_SEL1;
      selectedTimer = TIMER_1;
      break;
    case 2:
      controlWord |= TIMER_SEL2;
      selectedTimer = TIMER_2;
      break;
    default:
      return 1;
  }

  if (sys_outb(TIMER_CTRL, controlWord) != 0) return 1;

  if (sys_outb(selectedTimer, LSB) != 0) return 1;
  if (sys_outb(selectedTimer, MSB) != 0) return 1;
  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  if( bit_no == NULL) return 1; 
  *bit_no = BIT(hook_id);
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != 0) return 1;
  return 0;
}

int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id) != 0) return 1; // turn off interrputs
  return 0;
}

void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (st == NULL || timer > 2 || timer < 0) 
    return 1;

  uint8_t RBC = (TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer)); // RB command construction
  if (sys_outb(TIMER_CTRL, RBC) != 0) 
    return 1;
  if (util_sys_inb(TIMER_0 + timer, st)) 
    return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                          enum timer_status_field field) {
  if (timer > 2)
  return 1;

  union timer_status_field_val val;

  switch (field) {
    case tsf_all:
      val.byte = st;
      break;

    case tsf_initial:
      val.in_mode = (st >> 4) & 0x03;
      break;

    case tsf_mode:
      val.count_mode = (st >> 1) & 0x07;
      break;

    case tsf_base:
      val.bcd = st & 0x01;
      break;

    default:
    return 1;
  }

  return timer_print_config(timer, field, val);
}
