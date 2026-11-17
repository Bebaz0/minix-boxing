# name of the program (Minix service)
PROG=lab5

# source code files to be compiled
SRCS = lab5.c

# additional compilation flags
CFLAGS += -pedantic -I../timer -I../keyboard

# path to external libraries
TIMER_LIB = ../timer/libtimer.a
KBD_LIB = ../keyboard/libkbd.a

# list of library dependencies
DPADD += ${LIBLCF} ${TIMER_LIB} ${KBD_LIB} ${LIB_NAME}
LDADD += -llcf -L../timer -ltimer -L../keyboard -lkbd -L. -lvideo

LIB_NAME = libvideo.a
LIB_SRCS = video.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

all: lib
lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# Build external libraries when needed
${TIMER_LIB}:
	${MAKE} -C ../timer lib

${KBD_LIB}:
	${MAKE} -C ../keyboard lib

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>