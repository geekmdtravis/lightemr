// file: note.h

#ifndef _note_h
#define _note_h

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "modstring.h"
#include "patient.h"
#include "defs.h"
#include "note_structure.h"

typedef struct Patient Patient;

char *Formatted_time(void);
Note *Note_create(char *mrn);
Note *Note_copy(Note *n);
Note *Note_add(Patient *p);
BOOL Note_destroy(Note *n);

#endif

// eof: note.h
