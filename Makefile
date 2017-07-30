#!/usr/bin/make -f

SHELL = /bin/bash
CC = gcc
CFLAGS = -O2 -g -std=c99 -Wall -Wextra -pedantic -Werror \
	 -Wshadow -Wfloat-equal -Wmissing-prototypes \
	 -Wstrict-prototypes -Wwrite-strings -Waggregate-return
CPPFLAGS = -I. -D_XOPEN_SOURCE=600
LDFLAGS = -L. 
LDLIBS =
OBJS = ciar.o
PROG = ciar

.PHONY : all 
all : $(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $(OBJS) $(LDLIBS)

%.o : %.c 
	$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	-rm $(OBJS) $(PROG)
	-rm *?~
