# name of the program (Minix service)
PROG=lab5

# source code files to be compiled
SRCS = lab5.c

# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -I../lab2

# list of library dependencies
TIMER_LIB = ../lab2/libtimer.a
DPADD += ${LIBLCF} ${LIB_NAME} ${TIMER_LIB} 
LDADD += -llcf -L. -lvideo ${TIMER_LIB}

LIB_NAME = libvideo.a
LIB_SRCS = video.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

all: lib
lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

${TIMER_LIB}:
	${MAKE} -C ../lab2 lib

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>