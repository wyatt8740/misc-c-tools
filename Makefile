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
override CFLAGS += -g

.PHONY: all

all: add-vpn-param case-insensitive-pattern killsuid quotify realpath-posix rgb2hex sleep-decimal which wineify

add-vpn-param: add-vpn-param.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

case-insensitive-pattern: case-insensitive-pattern.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

quotify: quotify.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

realpath-posix: realpath-posix.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

rgb2hex: rgb2hex.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

sleep-decimal: sleep-decimal.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

which: which.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

wineify: wineify.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

killsuid: killsuid.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f case-insensitive-pattern killsuid quotify realpath-posix sleep-decimal which wineify

# Strip will die on nonexistant files but will still strip whatever it can
# first
.PHONY: strip

strip:
	$(STRIP) -S case-insensitive-pattern quotify realpath-posix sleep-decimal which wineify
