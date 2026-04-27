#include "video.h"

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <minix/sysutil.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

#define BIOS_VIDEO_INT 0x10
#define VBE_SET_MODE 0x4F02
#define VBE_CALL_SUPPORTED 0x4F
#define VBE_CALL_SUCCESS 0x00

/* Static global variables */
static char *video_mem;          /* frame-buffer VM address */
static vbe_mode_info_t vmi;      /* VBE mode info */
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel */
static unsigned vram_base;       /* VRAM physical base address */
static unsigned vram_size;       /* VRAM size in bytes */

void *(vg_init)(uint16_t mode) {
  if (vbe_get_mode_info(mode, &vmi) != OK) {
    printf("%s: vbe_get_mode_info(0x%03X) failed\n", __func__, mode);
    return NULL;
  }

  bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;
  vram_base = vmi.PhysBasePtr;
  vram_size = vmi.XResolution * vmi.YResolution * bytes_per_pixel;

  int r;
  struct minix_mem_range mr;
  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
    printf("%s: sys_privctl() failed with %d\n", __func__, r);
    return NULL;
  }

  video_mem = (char *) vm_map_phys(SELF, (void *) mr.mr_base, vram_size);
  if (video_mem == MAP_FAILED) {
    printf("%s: vm_map_phys() failed\n", __func__);
    return NULL;
  }

  reg86_t r86;
  memset(&r86, 0, sizeof(r86));

  r86.intno = BIOS_VIDEO_INT;
  r86.ax = VBE_SET_MODE;
  r86.bx = BIT(14) | mode;

  if (sys_int86(&r86) != OK) {
    printf("%s: sys_int86() failed\n", __func__);
    return NULL;
  }

  if (r86.ah != VBE_CALL_SUCCESS || r86.al != VBE_CALL_SUPPORTED) {
    printf("%s: VBE call failed AH=0x%02X AL=0x%02X\n", __func__, r86.ah, r86.al);
    return NULL;
  }

  return video_mem;
}
