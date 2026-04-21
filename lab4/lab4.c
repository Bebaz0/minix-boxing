// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "mouse.h"
#include "../lab2/timer.h"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  //lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  //lcf_log_output("/home/lcom/labs/lab4/output.txt");

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
    uint8_t bit_no;
    uint32_t packets_read = 0;
    uint8_t packet_bytes[3];
    int byte_index = 0;

    if (mouse_subscribe_interrupts(&bit_no) != 0) return 1;

    if (mouse_enable_data_reporting() != 0) return 1; 

    int ipc_status;
    message msg;

    // 3. Loop de interrupções
    while (packets_read < cnt) {
        if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & bit_no) {

                        mouse_ih(); 

                        uint8_t current_byte = get_mouse_byte();

                        if (byte_index == 0 && !(current_byte & BIT(3))) continue;

                        packet_bytes[byte_index] = current_byte;
                        byte_index++;

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

    mouse_write_cmd(MOUSE_DISABLE_DATA);
    mouse_unsubscribe_interrupts();

    return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  uint8_t m_bit, t_bit;
  uint8_t packet_bytes[3];
  int byte_index = 0;

  if (mouse_subscribe_interrupts(&m_bit) != 0) return 1;
  if (timer_subscribe_int(&t_bit) != 0) return 1;

  if (mouse_write_cmd(MOUSE_ENABLE_DATA) != 0) return 1;

  int ipc_status;
  message msg;
  int frequency = sys_hz();


  while (timer_get_counter() < (idle_time * frequency)) {
        
      if (driver_receive(ANY, &msg, &ipc_status) != 0) continue;

      if (is_ipc_notify(ipc_status)) {
          switch (_ENDPOINT_P(msg.m_source)) {
              case HARDWARE:
                
                  if (msg.m_notify.interrupts & t_bit) {
                      timer_int_handler();
                  }

           
                  if (msg.m_notify.interrupts & m_bit) {
                      mouse_ih();
                      uint8_t current_byte = get_mouse_byte();

                      if (byte_index == 0 && !(current_byte & BIT(3))) continue;

                      packet_bytes[byte_index] = current_byte;
                      byte_index++;

                        
                      if (byte_index == 3) {
                          struct packet p;
                          mouse_parse_packet(packet_bytes, &p);
                          mouse_print_packet(&p);
                            
                          byte_index = 0;

                      }
                  }
                  break;
          }
      }
  }

    mouse_write_cmd(MOUSE_DISABLE_DATA); 
    mouse_unsubscribe_interrupts();
    timer_unsubscribe_int();

    return 0;
}
