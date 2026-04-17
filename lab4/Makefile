# name of the program (Minix service)
PROG=lab4

# source code files to be compiled
SRCS = lab4.c

# additional compilation flags
CFLAGS += -pedantic -DLAB4

# include headers do lab2 (se fores usar timer no async depois)
CFLAGS += -I../lab2

# libraries
DPADD += ${LIBLCF} ${LIB_NAME} ../lab2/libtimer.a
LDADD += -L. -lmouse -L../lab2 -ltimer -llcf

# mouse library
LIB_NAME = libmouse.a
LIB_SRCS = mouse.c utils.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

all: lib
lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

# include LCOM's makefile
.include <minix.lcom.mk>
