#
# Makefile for getopt example
#
PROGRAMS=getopt-ex

all:	$(PROGRAMS)

getopt-ex:	getopt-ex.c
	gcc -Wall -o getopt-ex getopt-ex.c

clean::
	/bin/rm -f $(PROGRAMS)
