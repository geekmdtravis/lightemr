CC=gcc

CFLAGS=-Wall -Wextra -ggdb

all: lightemr


debug: main.o interface.o patient_add.o patient.o modstring.o
	$(CC) $(CFLAGS) main.o interface.o patient_add.o patient.o modstring.o -o lightemr

lightemr: main.o interface.o patient_add.o patient.o modstring.o
	$(CC) main.o interface.o patient_add.o patient.o modstring.o -o lightemr

clean:
	rm -f *.o *.c~ *.h~ Makefile~ lightemr
