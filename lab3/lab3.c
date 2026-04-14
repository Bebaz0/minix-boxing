#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include "timer.h"

#include <stdbool.h>
#include <stdint.h>

#include "i8042.h"
#include "kbc.h"

#define DELAY_US 20000
 

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int ipc_status, r;
  message msg;

  uint8_t bit_no;
  uint32_t irq_set;

  if (kbc_subscribe_int(&bit_no) != 0) return 1;

  irq_set = BIT(bit_no);

  uint8_t bytes[2];
  uint8_t size = 0;
  bool done = false;

  while (!done) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d\n", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {

        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) {

            kbc_ih();

            if (kbc_error) break;

            if (scancode == TWO_BYTE_CODE) {
              bytes[0] = scancode;
              size = 2;
            }
            else {

              if (size == 2) {
                bytes[1] = scancode;

                bool make = !(bytes[1] & BIT(7));
                kbd_print_scancode(make, 2, bytes);

                if (bytes[1] == ESC_BREAK_CODE)
                  done = true;

                size = 0;
              }
              else {
                bytes[0] = scancode;

                bool make = !(bytes[0] & BIT(7));
                kbd_print_scancode(make, 1, bytes);

                if (bytes[0] == ESC_BREAK_CODE)
                  done = true;
              }
            }
          }
          break;

        default:
          break;
      }
    }
  }

  if (kbc_unsubscribe_int() != 0) return 1;

  return 0;
}

int(kbd_test_poll)() {
  uint8_t status, data;
  uint8_t bytes[2];
  uint8_t size = 0;
  bool done = false;

  while (!done) {
    if (util_sys_inb(KBC_ST_REG, &status) != 0)
      return 1;

    if (status & KBC_OBF) {
      if (util_sys_inb(KBC_OUT_BUF, &data) != 0)
        return 1;

      if ((status & (KBC_PAR_ERR | KBC_TO_ERR)) == 0) {
        if (data == TWO_BYTE_CODE) {
          bytes[0] = data;
          size = 2;
        }
        else {
          if (size == 2) {
            bytes[1] = data;
            bool make = !(bytes[1] & BIT(7));
            kbd_print_scancode(make, 2, bytes);

            if (bytes[1] == ESC_BREAK_CODE)
              done = true;

            size = 0;
          }
          else {
            bytes[0] = data;
            bool make = !(bytes[0] & BIT(7));
            kbd_print_scancode(make, 1, bytes);

            if (bytes[0] == ESC_BREAK_CODE)
              done = true;
          }
        }
      }
    }

    tickdelay(micros_to_ticks(DELAY_US));
  }

  // reativar interrupções do teclado
  if (kbc_enable_int() != 0)
    return 1;

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status, r;
  message msg;

  uint8_t kbd_bit_no, timer_bit_no;
  uint32_t kbd_irq_set, timer_irq_set;

  if (kbc_subscribe_int(&kbd_bit_no) != 0) return 1;
  if (timer_subscribe_int(&timer_bit_no) != 0) {
    kbc_unsubscribe_int();
    return 1;
  }

  kbd_irq_set = BIT(kbd_bit_no);
  timer_irq_set = BIT(timer_bit_no);

  uint8_t bytes[2];
  uint8_t size = 0;
  bool done = false;

  int idle_ticks = 0;

  while (!done) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d\n", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & timer_irq_set) {
            timer_int_handler();
            idle_ticks++;

            if (idle_ticks >= n * 60) {
              done = true;
            }
          }

          if (msg.m_notify.interrupts & kbd_irq_set) {
            kbc_ih();

            if (kbc_error) break;

            idle_ticks = 0; /* reset por atividade do teclado */

            if (scancode == TWO_BYTE_CODE) {
              bytes[0] = scancode;
              size = 2;
            }
            else {
              if (size == 2) {
                bytes[1] = scancode;
                bool make = !(bytes[1] & BIT(7));
                kbd_print_scancode(make, 2, bytes);

                if (bytes[1] == ESC_BREAK_CODE)
                  done = true;

                size = 0;
              }
              else {
                bytes[0] = scancode;
                bool make = !(bytes[0] & BIT(7));
                kbd_print_scancode(make, 1, bytes);

                if (bytes[0] == ESC_BREAK_CODE)
                  done = true;
              }
            }
          }

          break;

        default:
          break;
      }
    }
  }

  if (timer_unsubscribe_int() != 0) return 1;
  if (kbc_unsubscribe_int() != 0) return 1;

  return 0;
}
