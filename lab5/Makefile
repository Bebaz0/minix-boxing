# name of the program (Minix service)
PROG=lab5 

# source code files
SRCS = lab5.c kbc.c utils.c

# flags
CFLAGS += -pedantic -DLAB5 -I../lab3

# libraries
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile
.include <minix.lcom.mk>