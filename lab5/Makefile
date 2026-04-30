# name of the program (Minix service)
PROG=lab5 

LAB3_PATH = ../lab3

.PATH: $(LAB3_PATH)

# source code files
SRCS = lab5.c video.c kbc.c utils.c

# flags
CFLAGS += -pedantic -DLAB5 -I../lab3

# libraries
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile
.include <minix.lcom.mk>