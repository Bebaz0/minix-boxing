# name of the program (Minix service)
PROG=lab4

# source code files to be compiled
SRCS = lab4.c timer.c

# additional compilation flags
CFLAGS += -pedantic -DLAB4

# include headers
CFLAGS += -I.

# libraries
DPADD += ${LIBLCF} ${LIB_NAME}
LDADD += -L. -lmouse -llcf

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
