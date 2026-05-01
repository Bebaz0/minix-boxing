#include <lcom/lcf.h>
#include "video.h"
#include "vbe.h"

int video_set_mode(uint16_t mode) {

    reg86_t reg;
    memset(&reg, 0, sizeof(reg));

    reg.intno = VBE_INTNO;
    reg.ah = VBE_AH;           
    reg.al = VBE_AL_SET_MODE;           
    reg.bx = mode | VBE_MODE_LINEAR_FRAME;

    if (sys_int86(&reg) != OK) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

    return 0;
}

