# name of the program (Minix service)
PROG=lab3

# source code files to be compiled
SRCS = lab3.c

# additional compilation flags
CFLAGS += -pedantic -DLAB3 -I../lab2

# list of library dependencies
DPADD += ${LIB_NAME} ../lab2/libtimer.a ${LIBLCF}
LDADD += -L. -lkbd -L../lab2 -ltimer -llcf

LIB_NAME = libkbd.a
LIB_SRCS = kbc.c utils.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

all: lib
lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

${TIMER_LIB}:
	${MAKE} -C ../lab2 lib

.include <minix.lcom.mk>