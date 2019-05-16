#
# ZiPhone Linux make by lex. Thank you ParrotGeek for putting the shared library in the executable.
#
CC=g++

CFLAGS=-g
INC=-I$(SRCDIR)

SRCDIR=src
OBJDIR=build

LDFLAGS=-lusb

OBJS=ziphone.o
LIBOBJS=libibooter.o

all: prepare ziphone 

VPATH=$(SRCDIR)

.cpp.o:
	$(CC) $(CFLAGS) -c $< $(INC) -o $(OBJDIR)/$@


ziphone: $(LIBOBJS) $(OBJS) 
	cd $(OBJDIR); $(CC) $(LDFLAGS) $^ -o $@

prepare:
	mkdir -p $(OBJDIR)

clean:
	 rm -rf $(OBJDIR)