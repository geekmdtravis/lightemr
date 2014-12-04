// file: note.h

#ifndef _note_h
#define _note_h

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "patient.h"
#include "defs.h"

typedef struct Note {
  char *mrn;
  char *title;
  char *author;
  char *time;
  char *replaced;
  char *text;
} Note;

Note *Note_create(char *mrn);
BOOL Note_destroy(Note *n);

#endif

// eof: note.h
