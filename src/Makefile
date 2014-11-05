CC=gcc

CFLAGS=-Wall -Wextra -ggdb

all: lightemr

lightemr: main.o interface.o patient_add.o patient.o
	$(CC) main.o interface.o patient_add.o patient.o -o lightemr

clean:
	rm -f main.c~ interface.c~ lightemr Makefile~ interface.h~ version.h~ clinical_tools.c~ clinical_tools.h~ test.c~ test patient.h~
	rm -f patient_add.c~ patient_add.h~
	rm -f main.o interface.o patient_add.o patient.o
