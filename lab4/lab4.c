// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include <mouse.h>

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
    uint8_t irq_set;
    int ipc_status;
    message msg;
    uint8_t packet_bytes[3];
    uint8_t byte_index = 0;
    uint32_t packets_read = 0;

    if (mouse_write_cmd(MOUSE_DISABLE_DR) != 0) return 1;
    if (mouse_subscribe_interrupts(&irq_set) != 0) return 1;
    if (mouse_write_cmd(MOUSE_ENABLE_DR) != 0) return 1;

    while (packets_read < cnt) {
        if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & irq_set) {
                        mouse_ih();
                        uint8_t byte = mouse_get_byte();

                        if (byte_index == 0 && !(byte & MOUSE_BIT3)) continue;

                        packet_bytes[byte_index++] = byte;

                        if (byte_index == 3) {
                            struct packet p;
                            mouse_parse_packet(packet_bytes, &p);
                            mouse_print_packet(&p);
                            byte_index = 0;
                            packets_read++;
                        }
                    }
                    break;
            }
        }
    }

    if (mouse_write_cmd(MOUSE_DISABLE_DR) != 0) return 1;
    if (mouse_unsubscribe_interrupts() != 0) return 1;
    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}