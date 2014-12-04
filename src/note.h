// file: note.h

#ifndef _note_h
#define _note_h

#include <stdlib.h>
#include "defs.h"

typedef struct Note {
  char *mrn;
  char *title;
  char *author;
  time_t *time;
  char *replaced;
  char *text;
} Note;

Note *Note_create(void);
BOOL Note_destroy(Note *n);

#endif

// eof: note.h
