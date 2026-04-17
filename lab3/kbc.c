#include <lcom/lcf.h>

#include "kbc.h"
#include "i8042.h"

#define DELAY_US 20000

static int hook_id = 1;

uint8_t scancode = 0;
bool kbc_error = false;

int kbc_subscribe_int(uint8_t *bit_no) {
  if (bit_no == NULL) return 1;

  *bit_no = hook_id;

  if (sys_irqsetpolicy(KBC_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0)
    return 1;

  return 0;
}

int kbc_unsubscribe_int() {
  if (sys_irqrmpolicy(&hook_id) != 0)
    return 1;

  return 0;
}

void (kbc_ih)() {
  uint8_t status;
  uint8_t data;

  if (util_sys_inb(KBC_ST_REG, &status) != 0) {
    kbc_error = true;
    return;
  }

  if (status & KBC_OBF) {
    if (util_sys_inb(KBC_OUT_BUF, &data) != 0) {
      kbc_error = true;
      return;
    }

    if (status & (KBC_PAR_ERR | KBC_TO_ERR)) {
      kbc_error = true;
      return;
    }

    scancode = data;
    kbc_error = false;
  }
}

int kbc_enable_int() {
  uint8_t status, cmd_byte;
  int retries = 5;

  while (retries--) {
    if (util_sys_inb(KBC_ST_REG, &status) != 0)
      return 1;

    if ((status & KBC_IBF) == 0) {
      if (sys_outb(KBC_CMD_REG, KBC_READ_CMD) != 0)
        return 1;
      break;
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  if (retries < 0) return 1;

  retries = 5;
  while (retries--) {
    if (util_sys_inb(KBC_ST_REG, &status) != 0)
      return 1;

    if (status & KBC_OBF) {
      if (util_sys_inb(KBC_OUT_BUF, &cmd_byte) != 0)
        return 1;

      if ((status & (KBC_PAR_ERR | KBC_TO_ERR)) != 0)
        return 1;

      break;
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  if (retries < 0) return 1;

  cmd_byte |= KBC_INT;

  retries = 5;
  while (retries--) {
    if (util_sys_inb(KBC_ST_REG, &status) != 0)
      return 1;

    if ((status & KBC_IBF) == 0) {
      if (sys_outb(KBC_CMD_REG, KBC_WRITE_CMD) != 0)
        return 1;
      break;
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  if (retries < 0) return 1;

  retries = 5;
  while (retries--) {
    if (util_sys_inb(KBC_ST_REG, &status) != 0)
      return 1;

    if ((status & KBC_IBF) == 0) {
      if (sys_outb(KBC_IN_BUF, cmd_byte) != 0)
        return 1;
      return 0;
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  return 1;
}
