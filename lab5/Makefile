# name of the program (Minix service)
PROG=lab5

# source code files to be compiled
SRCS = lab5.c

# additional compilation flags
CFLAGS += -pedantic -I../lab2 -I../lab3

# path to external libraries
TIMER_LIB = ../lab2/libtimer.a
KBD_LIB = ../lab3/libkbd.a

# list of library dependencies
DPADD += ${LIBLCF} ${TIMER_LIB} ${KBD_LIB} ${LIB_NAME}
LDADD += -llcf -L../lab2 -ltimer -L../lab3 -lkbd -L. -lvideo

LIB_NAME = libvideo.a
LIB_SRCS = video.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

all: lib
lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# Build external libraries when needed
${TIMER_LIB}:
	${MAKE} -C ../lab2 lib

${KBD_LIB}:
	${MAKE} -C ../lab3 lib

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>