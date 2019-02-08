
#Makefile for program hello
 
program := splitfile
 
sources := $(wildcard *.c)
headers := $(wildcard *.h)
 
objects := $(sources:.c=.o)
deps    := $(sources:.c=.d)
 
CC      := g++
SHARED  := -shared
FPIC    := -fPIC
CFLAGS  := -g -Wall -Werror -pthread -I./Include
LDFLAGS := 
 
RM      := rm -f

me      := Makefile
 
all:    $(program)
 
splitfile:  $(objects)
		$(CC) -o $@ $(CFLAGS) $(objects) $(LDFLAGS) $(LDLIBS)

clean:
		$(RM) $(objects)
		$(RM) $(deps)
		$(RM) $(program)

-include $(deps)
