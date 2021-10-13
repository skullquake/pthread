#CC=x86_64-linux-gnu-gcc-9
#CC=x86_64-w64-mingw32-gcc-9.3-posix
ifeq ($(CC),)
	CC=gcc
endif
SRC=./src/a.c
COMPILERVERSION=$(shell $(CC) -dumpversion)
TGT_MACHINE=$(shell $(CC) -dumpmachine)
LIBNAM=$(shell basename `pwd`)
CFLAGS+=-Wall -I./src
LDFLAGS+=-lpthread
ifneq (,$(findstring mingw,$(TGT_MACHINE)))
	#customize mingw
	ifneq (,$(findstring posix,$(TGT_MACHINE)))
		#customize mingw posix
	else
		#customize mingw nonposix
	endif
else
	#customize linux
endif
#set binary extension
ifneq (,$(findstring mingw,$(TGT_MACHINE)))
	BINEXT=.exe
else
	BINEXT=.out
endif
OUTDIR=./bin
BINDIR=$(OUTDIR)/$(TGT_MACHINE)
BIN:=$(BINDIR)/$(LIBNAM)$(BINEXT)
SRC:=$(shell find $(SRCDIR) -name '*.c')
OBJS:=$(addprefix $(BINDIR)/,$(SRC:%.c=%.o))
CFLAGS=-I./include
all:$(BIN)
$(BIN):$(OBJS)
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CC)\
		$(CFLAGS)\
		$(OBJS)\
		$(LDFLAGS)\
		-o $(BIN)
$(BINDIR)/%.o: %.c
	@printf "generating $@...\n"
	@mkdir -p $(@D)
	@$(CC)\
		$(CFLAGS)\
		-c $<\
		$(LDFLAGS)\
		-o $@
.phony:clean
clean:
	@rm -r ./bin
run:$(BIN)
	$(BIN)


