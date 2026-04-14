#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  if (timer > 2) return 1;
  if (freq == 0) return 1;

  uint32_t div = TIMER_FREQ / freq;
  if (div > 0xFFFF) return 1; //(16 bits)

  uint8_t st;
  if (timer_get_conf(timer, &st) != 0) return 1;

  uint8_t control = (timer << 6) | TIMER_LSB_MSB | (st & 0x0F);

  if (sys_outb(TIMER_CTRL, control) != 0) return 1;

  uint8_t lsb, msb;
  if (util_get_LSB(div, &lsb) != 0) return 1;
  if (util_get_MSB(div, &msb) != 0) return 1;

  if (sys_outb(TIMER_0 + timer, lsb) != 0) return 1;
  if (sys_outb(TIMER_0 + timer, msb) != 0) return 1;

  return 0;
}

static int hook_id = 0;
int (timer_subscribe_int)(uint8_t *bit_no) {
  if (bit_no == NULL) return 1;

  *bit_no = hook_id;

  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != 0)
    return 1;

  return 0;
}

int (timer_unsubscribe_int)() {
  if (sys_irqrmpolicy(&hook_id) != 0)
    return 1;

  return 0;
}

int counter = 0;
void (timer_int_handler)() {
  counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
    if (st == NULL) return 1;
    if (timer > 2) return 1;

    uint8_t rb_cmd = BIT(7) | BIT(6) | BIT(5) | BIT(timer + 1);

    if (sys_outb(TIMER_CTRL, rb_cmd) != 0) return 1;
    if (util_sys_inb(TIMER_0 + timer, st) != 0) return 1;

    return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  union timer_status_field_val val;

  switch (field) {
    case tsf_all:
      val.byte = st;
      break;

    case tsf_initial:
      switch ((st >> 4) & 0x03) {
        case 1:
          val.in_mode = LSB_only;
          break;
        case 2:
          val.in_mode = MSB_only;
          break;
        case 3:
          val.in_mode = MSB_after_LSB;
          break;
        default:
          val.in_mode = INVAL_val;
          break;
      }
      break;

    case tsf_mode:
      val.count_mode = (st >> 1) & 0x07;
      if (val.count_mode == 6)
        val.count_mode = 2;
      else if (val.count_mode == 7)
        val.count_mode = 3;
      break;

    case tsf_base:
      val.bcd = st & 0x01;
      break;

    default:
      return 1;
  }

  return timer_print_config(timer, field, val);
}
