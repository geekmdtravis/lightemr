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

/**********************************************
 * Formatted_time()
 **********************************************
 * This function returns a date and time string
 * literal. The Note n->time object is where
 * this is primarily intended to be used. However
 * it might have uses in different places.
 * TODO: consider moving this to a different
 * file.
 *********************************************/
char *Formatted_time(void);

/****************************************
 *Note_create(char *mrn)
 ****************************************
 * Initialize a note object and return it.
 * All field objects are defined.
 ***************************************/
Note *Note_create(char *mrn);

/****************************************
 * Note_copy()
 ****************************************
 * Returns a note object. This is primarily
 * utilized when a note is found in the
 * database and we need to extract a single
 * note from the liked list of Note_query
 * nodes. Was having difficulty plucking
 * it from the linked list and destroying
 * the object so created the copy function
 * for both the patient and the note
 * to circumvent that problem.
 ***************************************/
Note *Note_copy(Note *n);

/***************************************
 * Note_add(Patient *p)
 **************************************
 * Create a new note and initialize the
 * values to the patient where appropriate.
 * Note type and text content of the note
 * will be input by user.
 * Return value is a note object.
 **************************************/
Note *Note_add(Patient *p);

/*********************************************
 * Note_destroy(Note *n)
 *********************************************
 * Clean up the heap where the note was
 * previously located.
 * Returns true on success;
 ********************************************/
BOOL Note_destroy(Note *n);

#endif

// eof: note.h
