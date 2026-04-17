#include <lcom/lcf.h>
#include <lcom/lab4.h>

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "mouse.h"

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");

  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  if (lcf_start(argc, argv))
    return 1;

  lcf_cleanup();

  return 0;
}

int(mouse_test_packet)(uint32_t cnt) {
  int ipc_status, r;
  message msg;

  uint8_t bit_no;
  uint32_t irq_set;

  if (mouse_enable_data_reporting() != 0) return 1;
  if (mouse_subscribe_int(&bit_no) != 0) return 1;

  irq_set = BIT(bit_no);

  uint8_t bytes[3];
  uint8_t idx = 0;
  uint32_t packets_read = 0;
  struct packet pp;

  while (packets_read < cnt) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d\n", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set) {
            mouse_ih();

            if (mouse_error) break;

            if (idx == 0) {
              if (mouse_byte & BIT(3)) {
                bytes[idx++] = mouse_byte;
              }
            }
            else {
              bytes[idx++] = mouse_byte;
            }

            if (idx == 3) {
              pp.bytes[0] = bytes[0];
              pp.bytes[1] = bytes[1];
              pp.bytes[2] = bytes[2];

              pp.lb = bytes[0] & BIT(0);
              pp.rb = bytes[0] & BIT(1);
              pp.mb = bytes[0] & BIT(2);

              pp.x_ov = bytes[0] & BIT(6);
              pp.y_ov = bytes[0] & BIT(7);

              pp.delta_x = (bytes[0] & BIT(4)) ? (0xFF00 | bytes[1]) : bytes[1];
              pp.delta_y = (bytes[0] & BIT(5)) ? (0xFF00 | bytes[2]) : bytes[2];

              mouse_print_packet(&pp);

              packets_read++;
              idx = 0;
            }
          }
          break;
        default:
          break;
      }
    }
  }

  if (mouse_disable_data_reporting() != 0) return 1;
  if (mouse_unsubscribe_int() != 0) return 1;

  return 0;
}
