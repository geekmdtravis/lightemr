CC=gcc

CFLAGS=-Wall -Wextra -ggdb

LINK=-l sqlite3

all: lightemr


debug: main.o interface.o patient_add.o patient.o modstring.o database.o
	$(CC) $(CFLAGS) main.o interface.o patient_add.o patient.o modstring.o database.o -o lightemr $(LINK)

lightemr: main.o interface.o patient_add.o patient.o modstring.o database.o
	$(CC) main.o interface.o patient_add.o patient.o modstring.o database.o -o lightemr $(LINK)

clean:
	rm -f *.o *.c~ *.h~ Makefile~ lightemr
