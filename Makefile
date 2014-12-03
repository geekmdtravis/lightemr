SHELL=/bin/sh

.SUFFIXES:
.SUFFIXES: .c .o

CC=gcc
SRC=./src/
DEPS=$(SRC)interface.o $(SRC)patient_add.o $(SRC)modstring.o $(SRC)database.o $(SRC)login.o $(SRC)clinical_tools.o

CFLAGS=-Wall -ggdb
DEBUGFLAGS=-Wall -Wextra -ggdb

LINK=-l sqlite3

all: lightemr

lightemr: main.o
	@echo "=============================="
	@echo "     BUILDING THE PROJECT"
	@echo "=============================="
	$(CC) $(SRC)main.o $(DEPS) -o lightemr $(LINK)
	@echo "=============================="
	rm -f *.o

main.o: $(SRC)main.o $(DEPS)


debug: main.o
	$(CC) $(SRC)main.o $(DEPS) -o lightemr $(LINK)

clean:
	@echo "=============================="
	@echo "  CLEANING PROJECT DIRECTORY"
	@echo "=============================="
	rm -f *.o *~ *\# Makefile~ lightemr lightemr.data
	@echo "=============================="
