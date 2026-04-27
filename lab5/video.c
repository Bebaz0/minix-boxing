#include "video.h"

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <minix/sysutil.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

static vbe_mode_info_t mode_info;
static void *video_mem;
static unsigned int vram_size;

void *(vg_init)(uint16_t mode) {
  if (vbe_get_mode_info(mode, &mode_info) != OK) {
    printf("%s: vbe_get_mode_info(0x%03X) failed\n", __func__, mode);
    return NULL;
  }

  struct minix_mem_range mr;
  mr.mr_base = mode_info.PhysBasePtr;
  vram_size = mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8);
  mr.mr_limit = mr.mr_base + vram_size;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) {
    printf("%s: sys_privctl() failed\n", __func__);
    return NULL;
  }

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
  if (video_mem == MAP_FAILED) {
    printf("%s: vm_map_phys() failed\n", __func__);
    return NULL;
  }

  reg86_t r86;
  memset(&r86, 0, sizeof(r86));

  r86.intno = 0x10;
  r86.ax = 0x4F02;
  r86.bx = BIT(14) | mode;

  if (sys_int86(&r86) != OK) {
    printf("%s: sys_int86() failed\n", __func__);
    return NULL;
  }

  return video_mem;
}
