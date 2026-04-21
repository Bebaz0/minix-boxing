# name of the program (Minix service)
PROG=lab4 

# source code files to be compiled
SRCS = lab4.c mouse.c utils.c kbc.c


# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -I../lab2

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf -L../lab2 -ltimer

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
