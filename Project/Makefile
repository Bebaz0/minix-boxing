PROG = game

VPATH = src:src/model:src/view:src/controller

SRCS = main.c \
       game.c \
       player.c \
       key_prompt.c \
       bubble.c \
       combat.c \
       render.c \
       controller.c

CFLAGS += -pedantic -Isrc -Isrc/model -Isrc/view -Isrc/controller -Iinclude -I../lab2 -I../lab3 -I../lab4 -I../lab5

VIDEO_LIB = ../lab5/libvideo.a
MOUSE_LIB = ../lab4/libmouse.a
KBD_LIB   = ../lab3/libkbd.a
TIMER_LIB = ../lab2/libtimer.a

DPADD += ${LIBLCF} ${VIDEO_LIB} ${MOUSE_LIB} ${KBD_LIB} ${TIMER_LIB}
LDADD += -llcf -L../lab5 -lvideo -L../lab4 -lmouse -L../lab3 -lkbd -L../lab2 -ltimer

${VIDEO_LIB}:
	${MAKE} -C ../lab5 lib

${MOUSE_LIB}:
	${MAKE} -C ../lab4 lib

${KBD_LIB}:
	${MAKE} -C ../lab3 lib

${TIMER_LIB}:
	${MAKE} -C ../lab2 lib

.include <minix.lcom.mk>
