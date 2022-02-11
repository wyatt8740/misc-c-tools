# Makefile for colorcheck

STRIP ?= strip
CC ?= cc
CXX ?= c++
CPP ?= cpp
AR ?= ar
LD ?= ld

INCLUDES ?= `pkg-config --cflags MagickCore MagickWand`
LIBS ?= `pkg-config --libs MagickCore MagickWand`

CFLAGS += -g -Wall $(INCLUDES) 
LDFLAGS += $(LIBS)

colorcheck: colorcheck.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

