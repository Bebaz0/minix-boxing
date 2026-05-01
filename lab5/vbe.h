#ifndef _VBE_H_
#define _VBE_H_

#include <lcom/lcf.h>

#define VBE_INTNO       0x10

#define VBE_AH              0x4F


#define VBE_AL_CTRL_INFO    0x00   
#define VBE_AL_MODE_INFO    0x01   
#define VBE_AL_SET_MODE     0x02   

#define BIOS_AH_SET_MODE    0x00   

#define BIOS_AL_TEXT_MODE   0x03  

#define VBE_MODE_LINEAR_FRAME   BIT(14)  

#define INDEXED_MODE 0x105

#endif 

