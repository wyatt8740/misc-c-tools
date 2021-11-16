# A simple Makefile for misc-c-tools
# by Wyatt Ward, 2021

# Tested working in GNU Make, smake (Schily tools, by Joerg Schilling),
# nmake (AT&T AST NMake, by Glenn Fowler), and SunPro Make (Sun Microsystems,
# fork maintained by Joerg Schlling; you may need CC=(your compiler) to be
# set).

.PHONY: all

all: case-insensitive-pattern quotify realpath-posix rgb2hex sleep-decimal wineify

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

wineify: wineify.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f case-insensitive-pattern quotify realpath-posix sleep-decimal wineify
