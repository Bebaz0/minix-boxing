PROG = proj

VPATH = src:src/model:src/view/core:src/view/screens:src/view/fighters:src/controller

SRCS = main.c \
       game.c \
       menu.c \
       char_select.c \
       animation.c \
       player.c \
       key_prompt.c \
       bubble.c \
       combat.c \
       render.c \
       menu_view.c \
       active_view.c \
       round_start_view.c \
       font.c \
       view_utils.c \
       sprites.c \
       controller.c \
       menu_controller.c \
       char_select_controller.c \
       active_controller.c \
       pause_controller.c \
       round_start_controller.c \
       game_over_controller.c \
       game_over_view.c \
       pause_view.c \
       leaderboard.c \
       leaderboard_view.c \
       leaderboard_controller.c \
       char_select_view.c \
       fighter_sprites.c \
       instructions_view.c

CFLAGS += -pedantic -Isrc -Isrc/model -Isrc/view/core -Isrc/view/screens -Isrc/view/fighters -Isrc/controller -Iinclude -I../timer -I../keyboard -I../mouse -I../video -I../rtc

VIDEO_LIB = ../video/libvideo.a
MOUSE_LIB = ../mouse/libmouse.a
KBD_LIB   = ../keyboard/libkbd.a
TIMER_LIB = ../timer/libtimer.a
RTC_LIB   = ../rtc/librtc.a

DPADD += ${LIBLCF} ${VIDEO_LIB} ${MOUSE_LIB} ${KBD_LIB} ${TIMER_LIB} ${RTC_LIB}
LDADD += -llcf -L../video -lvideo -L../mouse -lmouse -L../keyboard -lkbd ../timer/timer.o -L../rtc -lrtc

${VIDEO_LIB}:
	${MAKE} -C ../video lib

${MOUSE_LIB}: ../mouse/mouse.c ../mouse/kbc.c ../mouse/utils.c ../mouse/mouse.h ../mouse/kbc.h ../mouse/i8042.h
	${MAKE} -C ../mouse lib

${KBD_LIB}:
	${MAKE} -C ../keyboard lib

${TIMER_LIB}:
	${MAKE} -C ../timer lib

${RTC_LIB}:
	${MAKE} -C ../rtc lib

.include <minix.lcom.mk>
