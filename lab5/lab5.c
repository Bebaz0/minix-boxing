#include <lcom/lcf.h>
#include <machine/int86.h>
#include <stdint.h>
#include <stdio.h>


int (video_test_init)(uint16_t mode, uint8_t delay) {
  reg86_t r;

  memset(&r, 0, sizeof(r));

  r.intno = 0x10;
  r.ax = 0x4F02;
  r.bx = mode | BIT(14);

  if (sys_int86(&r) != OK) {
    printf("video_test_init: sys_int86 failed\n");
    return 1;
  }

  sleep(delay);

  if (vg_exit() != 0) return 1;

  return 0;
}