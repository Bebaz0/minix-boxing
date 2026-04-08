#include <lcom/lcf.h>

#include "kbc.h"
#include "i8042.h"

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
