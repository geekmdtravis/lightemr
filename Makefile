all:
	gcc -Wall -Wextra -ggdb -g -o lightemr main.c interface.c
clean:
	rm -f main.c~ interface.c~ lightemr Makefile~ interface.h~ version.h~ clinical_tools.c~ clinical_tools.h~
