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
	$(CC) main.o interface.o patient_add.o patient.o modstring.o database.o login.o clinical_tools.o -o lightemr $(LINK)
	@echo "=============================="
	rm -f *.o

main.o: interface.o patient_add.o patient.o modstring.o database.o login.o clinical_tools.o

debug: main.o 
	$(CC) main.o interface.o patient_add.o patient.o modstring.o database.o login.o clinical_tools.o -o lightemr $(LINK)

clean:
	@echo "=============================="
	@echo "  CLEANING PROJECT DIRECTORY"
	@echo "=============================="
	rm -f *.o *~ *# Makefile~ lightemr lightemr.data
	@echo "=============================="
