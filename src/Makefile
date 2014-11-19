SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .c .o

CC=gcc

CFLAGS=-Wall -ggdb
DEBUGFLAGS=-Wall -Wextra -ggdb

LINK=-l sqlite3

all: lightemr

lightemr: main.o
	@echo "=============================="
	@echo "     BUILDING THE PROJECT"
	@echo "=============================="
	$(CC) main.o interface.o patient_add.o patient.o modstring.o database.o -o lightemr $(LINK)
	@echo "=============================="

main.o: interface.o patient_add.o patient.o modstring.o database.o

debug: main.o 
	$(CC) $(DEBUGFLAGS) main.o interface.o patient_add.o patient.o modstring.o database.o -o lightemr $(LINK)

clean:
	@echo "=============================="
	@echo "  CLEANING PROJECT DIRECTORY"
	@echo "=============================="
	rm -f *.o *.c~ *.h~ Makefile~ lightemr
	@echo "=============================="
