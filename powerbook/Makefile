# A simple Makefile for misc-c-tools
# by Wyatt Ward, 2021

# Tested working in GNU Make, smake (Schily tools, by Joerg Schilling),
# nmake (AT&T AST NMake, by Glenn Fowler), and SunPro Make (Sun Microsystems,
# fork maintained by Joerg Schlling; you may need CC=(your compiler) to be
# set).

STRIP ?= strip
CC ?= cc
CXX ?= c++
CPP ?= cpp
AR ?= ar
LD ?= ld
# override CFLAGS += -g
OPTIMIZE=-O2

# OBJ = file_io.o fanlimit.o temp.o
%.o: %.c $(DEPS)

.PHONY: all

all: fanlimit temp

file_io.o: file_io.c file_io.h
	$(CC) $(OPTIMIZE) -c -o $@ $< $(CFLAGS)

fanlimit.o: fanlimit.c fanlimit.h
	$(CC) $(OPTIMIZE) -c -o $@ $< $(CFLAGS)

temp.o: temp.c temp.h
	$(CC) $(OPTIMIZE) -c -o $@ $< $(CFLAGS)

fanlimit: fanlimit.o file_io.o
	$(CC) $(OPTIMIZE) -o $@ $^ $(CFLAGS) $(LDFLAGS)

temp: temp.o file_io.o
	$(CC) $(OPTIMIZE) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o temp fanlimit

# Strip will die on nonexistant files but will still strip whatever it can
# first
.PHONY: strip

strip:
	$(STRIP) -S temp fanlimit
