
#Makefile for program hello

program := myprog

srcdir := src
objdir := obj
bindir := bin

bin := $(bindir)/$(program)

cc_sources := $(wildcard $(srcdir)/*.cc)
c_sources := $(wildcard $(srcdir)/*.c)
 
cc_objects := $(addprefix $(objdir)/,$(notdir $(cc_sources:.cc=.o)))
c_objects  := $(addprefix $(objdir)/,$(notdir $(c_sources:.c=.o)))
objs := $(cc_objects) $(c_objects)
deps := $(objs:%.o=%.d)

CC      := g++
SHARED  := -shared
FPIC    := -fPIC
CFLAGS  := -g -O2 -Wall -Werror -pthread -I./include
CCFLAGS  := -g -O2 -std=c++11 -Wall -Werror -pthread -I./include
#LDFLAGS := -lstdc++
LDFLAGS := 
 
RM      := rm -f

me      := Makefile
 
all:    $(bin)

.PHONY: $(program)
$(program):  $(bin)
 
$(bin):  $(cc_objects) | $(bindir)
	$(CC) $^ $(LDFLAGS) -o $@

$(bindir):
	mkdir $(bindir)

$(cc_objects): | $(objdir)

$(objdir):
	mkdir $(objdir)

$(objdir)/%.o:  $(srcdir)/%.cc
	$(CC) $(CCFLAGS) -c $< -o $@

$(objdir)/%.o:  $(srcdir)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) $(cc_objects)
		$(RM) $(c_objects)
		$(RM) $(deps)
		$(RM) $(bin)

.PHONY: info
info:
	@echo "CC   = $(CC)"
	@echo "CFLAGS  = $(CFLAGS)"
	@echo "CCFLAGS= $(CCFLAGS)"
	@echo "CC_SRCS = $(cc_sources)"
	@echo "CC_OBJS = $(cc_objects)"
	@echo "C_SRCS  = $(c_sources)"
	@echo "C_OBJS  = $(c_objects)"
	@echo "OBJS    = $(objs)"
	@echo "PROG    = $(program)"
	@echo "BIN     = $(bin)"

-include $(deps)
