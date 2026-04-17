#include <lcom/lcf.h>

#include "mouse.h"
#include "i8042.h"

#define DELAY_US 20000

static int hook_id = MOUSE_IRQ;

static uint8_t packet_bytes[3];

uint8_t mouse_byte = 0;
bool mouse_error = false;

int mouse_subscribe_int(uint8_t *bit_no) {
  if (bit_no == NULL) return 1;

  *bit_no = hook_id;

  if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0)
    return 1;

  return 0;
}

int mouse_unsubscribe_int() {
  if (sys_irqrmpolicy(&hook_id) != 0)
    return 1;

  return 0;
}

void (mouse_ih)() {
  uint8_t status;
  uint8_t data;

  if (util_sys_inb(KBC_ST_REG, &status) != 0) {
    mouse_error = true;
    return;
  }

  if (status & KBC_OBF) {
    if (util_sys_inb(KBC_OUT_BUF, &data) != 0) {
      mouse_error = true;
      return;
    }

    if ((status & (KBC_PAR_ERR | KBC_TO_ERR)) != 0) {
      mouse_error = true;
      return;
    }

    if (!(status & KBC_AUX)) {
      mouse_error = true;
      return;
    }

    mouse_byte = data;
    mouse_error = false;
  }
}

int mouse_write_cmd(uint8_t cmd) {
  uint8_t status, response;
  int retries = 5;

  while (retries--) {
    if (util_sys_inb(KBC_ST_REG, &status) != 0) return 1;

    if ((status & KBC_IBF) == 0) {
      if (sys_outb(KBC_CMD_REG, WRITE_TO_MOUSE) != 0) return 1;
      break;
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  if (retries < 0) return 1;

  retries = 5;
  while (retries--) {
    if (util_sys_inb(KBC_ST_REG, &status) != 0) return 1;

    if ((status & KBC_IBF) == 0) {
      if (sys_outb(KBC_IN_BUF, cmd) != 0) return 1;
      break;
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  if (retries < 0) return 1;

  retries = 5;
  while (retries--) {
    if (util_sys_inb(KBC_ST_REG, &status) != 0) return 1;

    if (status & KBC_OBF) {
      if (util_sys_inb(KBC_OUT_BUF, &response) != 0) return 1;

      if ((status & (KBC_PAR_ERR | KBC_TO_ERR)) != 0) return 1;

      if (response == ACK) return 0;
      if (response == NACK || response == ERROR) return mouse_write_cmd(cmd);
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  return 1;
}

int mouse_disable_data_reporting() {
  return mouse_write_cmd(DISABLE_DATA_REPORTING);
}

void mouse_parse_packet(struct packet *pp) {
  pp->bytes[0] = packet_bytes[0];
  pp->bytes[1] = packet_bytes[1];
  pp->bytes[2] = packet_bytes[2];

  pp->lb = packet_bytes[0] & BIT(0);
  pp->rb = packet_bytes[0] & BIT(1);
  pp->mb = packet_bytes[0] & BIT(2);

  pp->x_ov = packet_bytes[0] & BIT(6);
  pp->y_ov = packet_bytes[0] & BIT(7);

  pp->delta_x = (packet_bytes[0] & BIT(4)) ? (0xFF00 | packet_bytes[1]) : packet_bytes[1];
  pp->delta_y = (packet_bytes[0] & BIT(5)) ? (0xFF00 | packet_bytes[2]) : packet_bytes[2];
}
