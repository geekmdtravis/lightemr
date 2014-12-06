SHELL=/bin/sh

.SUFFIXES: .c .o

CC=gcc

CFLAGS=-Wall -ggdb
DEBUGFLAGS=-Wall -Wextra -ggdb
DEPS=main.o interface.o patient.o modstring.o \
	database.o login.o clinical_tools.o note.o

LINK=-l sqlite3

all: lightemr

lightemr: main.o
	@echo "=============================="
	@echo "     BUILDING THE PROJECT"
	@echo "=============================="
	$(CC) $(DEPS) -o lightemr $(LINK)
	@echo "=============================="

main.o: $(DEPS)

clean:
	@echo "=============================="
	@echo "  CLEANING PROJECT DIRECTORY"
	@echo "=============================="
	rm -f *.o *~ *\# Makefile~ lightemr lightemr.data
	@echo "=============================="
