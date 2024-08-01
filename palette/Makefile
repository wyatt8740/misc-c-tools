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
override CFLAGS += -Wall

.PHONY: all

all: pal2bmp bmp2pal

pal2bmp: pal2bmp.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

bmp2pal: bmp2pal.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f pal2bmp bmp2pal

# Strip will die on nonexistant files but will still strip whatever it can
# first
.PHONY: strip

strip:
	$(STRIP) -S pal2bmp bmp2pal
