// file: database.h

#ifndef _database_h
#define _database_h

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "interface.h"
#include "patient.h"
#include "database.h"
#include "note.h"
#include "modstring.h"
#include "defs.h"

// No idea why this is necessary considering everything is working
// in all other includes. One workaround I've found is to put the
// definitions into a separate header file, but this doesn't make
// any sense to me.
typedef struct Patient Patient;
typedef struct Note Note;

/* The PQR struct was created specifically to deal with a
   challenge presented by the need for callback functions
   in the sqlite3_exec() function. A list of patients needed
   to be passed to through the void pointer argument
   designated 'void *udp' below. However, a way to count the
   number of results and loop through them was also required.
   So this struct was created to be used with the callback
   function so that the 'count' field can be incremented each
   time it enters callback, and this allows us to augment
   the members of the Patient *resultList[] pointer array.

   EX: sqlite3_exec(database, sql, callback, void_ptr, error_msg);
   
   *** 'void_ptr' is declared below as void *udp. It is provided
       to the callback function.

       callback(void_ptr, int num_c, char *c_vals[], char *c_names[]);

   ***  Inside of the callback function, void_ptr can be type-cast.
        NOTE: num_c = number of columns
	      c_vals[] = values for each column in a row
	      c_names[] = names for each column in a row
	NOTE: This returns only one column at a time! However, inside of
	      the sqlite3_exec() function it will be called as many times
	      as there are results.

  PQR contains a patient list and a counter. Inside of the callback,
  when passed by reference, the counter can be augmented and the patient
  list can be appended. However, because only one argument can be
  provided to the callback function by design the PQR struct was created.
       
*/
typedef struct Patient_query_result {
  Patient *resultList[MAX_RESULTS];
  int count;
} PQR;

int Patient_notes_table_create(sqlite3 *db);
char *Create_add_note_query(const Note *n);
int Patient_demographics_table_create(sqlite3 *db);
char *Create_add_user_query(const Patient *p);
Patient *Patient_lookup(sqlite3 *db, const char *identifier, const char *querymod);
int Patient_find_callback(void *upd, int num_c, char *c_vals[], char *c_names[]);
int Patient_select(const struct Patient_query_result *pqr, const char *last);

#endif

// eof: database.h

