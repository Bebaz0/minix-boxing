#ifndef FIGHTER_H
#define FIGHTER_H

#include "config.h"
#include <lcom/lcf.h>

#include "fighter_idle0.xpm"
#include "fighter_idle1.xpm"
#include "fighter_idle2.xpm"
#include "fighter_idle3.xpm"

#define FIGHTER_W 192

static xpm_map_t fighter_idle_frames[FIGHTER_IDLE_FRAME_COUNT] = {
  fighter_idle0_xpm,
  fighter_idle1_xpm,
  fighter_idle2_xpm,
  fighter_idle3_xpm
};


#endif /* FIGHTER_H */
