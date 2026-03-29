#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
    if (freq == 0 || freq > TIMER_FREQ) return 1;

    uint8_t status;
    if (timer_get_conf(timer, &status) != OK) return 1;

    uint8_t control_word = (timer << 6) | 0x30 | (status & 0x0F);

    if (sys_outb(TIMER_CTRL, control_word) != OK) return 1;

    uint16_t divider = TIMER_FREQ / freq;

    uint8_t lsb, msb;
    util_get_LSB(divider, &lsb);
    util_get_MSB(divider, &msb);

    uint8_t timer_port = TIMER_0 + timer;
    if (sys_outb(timer_port, lsb) != OK) return 1;
    if (sys_outb(timer_port, msb) != OK) return 1;

    return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (timer>2 || st==NULL)return 1;

  uint8_t cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

   if(sys_outb(TIMER_CTRL, cmd)!=0)return 1;

  if(util_sys_inb(TIMER_0 + timer,st)!=0)return 1;

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,enum timer_status_field field) {
  union timer_status_field_val valor;

  switch (field){

    case tsf_all: valor.byte=st;
    break;

    case tsf_initial: valor.in_mode=(st & (BIT(4)|BIT(5)))>>4;
    break;

    case tsf_mode: valor.count_mode=(st & (BIT(1)|BIT(2)|BIT(3)))>>1;
    break;

    case tsf_base: valor.bcd=(st & BIT(0));
    break;
  default:
    return 1;
  }
  return timer_print_config(timer,field,valor);
}
