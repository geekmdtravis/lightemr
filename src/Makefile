CC=gcc

CFLAGS=-Wall -Wextra -ggdb

all: lightemr

lightemr: main.o interface.o patient_add.o patient.o
	$(CC) $(CFLAGS) main.o interface.o patient_add.o patient.o -o lightemr

clean:
	rm -f *.o *.c~ *.h~ Makefile~ lightemr
