PROG = proj

VPATH = src:src/model:src/view:src/controller

SRCS = main.c \
       game.c \
       menu.c \
       char_select.c \
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

CFLAGS += -pedantic -Isrc -Isrc/model -Isrc/view -Isrc/controller -Iinclude -I../lab2 -I../lab3 -I../lab4 -I../lab5 -I../lab1

VIDEO_LIB = ../lab5/libvideo.a
MOUSE_LIB = ../lab4/libmouse.a
KBD_LIB   = ../lab3/libkbd.a
TIMER_LIB = ../lab2/libtimer.a
RTC_LIB   = ../lab1/librtc.a

DPADD += ${LIBLCF} ${VIDEO_LIB} ${MOUSE_LIB} ${KBD_LIB} ${TIMER_LIB} ${RTC_LIB}
LDADD += -llcf -L../lab5 -lvideo -L../lab4 -lmouse -L../lab3 -lkbd ../lab2/timer.o -L../lab1 -lrtc

${VIDEO_LIB}:
	${MAKE} -C ../lab5 lib

${MOUSE_LIB}: ../lab4/mouse.c ../lab4/kbc.c ../lab4/utils.c ../lab4/mouse.h ../lab4/kbc.h ../lab4/i8042.h
	${MAKE} -C ../lab4 lib

${KBD_LIB}:
	${MAKE} -C ../lab3 lib

${TIMER_LIB}:
	${MAKE} -C ../lab2 lib

${RTC_LIB}:
	${MAKE} -C ../lab1 lib

.include <minix.lcom.mk>
