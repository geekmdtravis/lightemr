// file: database.h

#ifndef _database_h
#define _database_h

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "patient.h"
#include "patient_structure.h"
#include "note.h"
#include "note_structure.h"
#include "defs.h"

/* The PQ_node was created specifically to deal with a
   challenge presented by the need for callback functions
   in the sqlite3_exec() function. A list of patients needed
   to be passed to through the void pointer argument
   designated 'void *udp' below. However, a way to count the
   number of results and loop through them was also required.
   So this data structure was created to be used with the callback
   function so that the 'count' field can be incremented each
   time it enters callback, and this allows us to augment
   the members of the PQ_node *linked_list;

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

  PQ_node contains a patient and an enumerated identifier. Inside of the
  callback, when passed by reference, the count can be augmented and the
  patient list can be appended. However, because only one argument can be
  provided to the callback function by design the PQ_node data structure
  was created.
*/
typedef struct Patient_query_node {
  int count;
  BOOL selected;
  Patient *pt;
  struct Patient_query_node *next;
  struct Patient_query_node *prev;
} PQ_node;

/*****************************
 * Similar to PQ_node, but for notes.
 ****************************/
typedef struct Note_query_node {
  int count;
  BOOL selected;
  Note *note;
  struct Note_query_node *next;
  struct Note_query_node *prev;
} NQ_node;
  


/******************************************************
              FORWARD DECLARATIONS
 *****************************************************/
// need to sort and explain these
NQ_node *NQ_node_alloc(void);
Note *Note_lookup(sqlite3 *db, char *identifier, char *field);
char *Create_note_lookup_query(char *identifier, char *field);
int Note_find_callback(void *udp, int c_num, char *c_vals[], char *c_names[]);
NQ_node *NQ_list_find_tail(NQ_node *n);
BOOL NQ_node_add(NQ_node *n);
BOOL NQ_list_pop(NQ_node *n);
BOOL NQ_list_purge(NQ_node *n);
BOOL NQ_node_destroy(NQ_node *n);



/*****************************************************
 Patient_lookup(): takes a database, the identifier
  that the user whishes to use to find a patient in
  the database, and the field in which the program
  will search columns for a match.
 RETURN: patient object if found, NULL if not
 *****************************************************/
Patient *Patient_lookup(sqlite3 *db, char *identifier, char *field);


/*****************************************************
  Patient_notes_table_create(): a simple function
   which executes a SQLite3 command to create our
   patient notes table.
 *****************************************************/
int Patient_notes_table_create(sqlite3 *db);


/*****************************************************
 Patient_demographics_table_create(): same as Patient_
   notes_table_create() but with demographic information.
 *****************************************************/
int Patient_demographics_table_create(sqlite3 *db);


/*****************************************************
  Patient_find_callback(): This is the callback function
   called by the sqlite3_exec() function. It is executed
   for each query match, inside of sqlite3_exec(). We are
   note privileged to it's inner code, so it's important
   to know what the callback does.

   void *udp: is a void pointer which, in this case,
              will be  passed a linked list head node
              to which it can query matches; of note
              an auto-incrementing mechanism was built
              into the linked list (Patient_query_node)
              data structure so that the list of results
              is enumerated can be easily searched.
   int num_c: number of columns in query result.
   char *c_vals[]: list of strings of column values returned
              for a query; remember, one query, no row of
              column cells are returned.
   char *c_names[]: list of strings of column names; unused
              in the present implementation.

 *****************************************************/
int Patient_find_callback(void *upd, int num_c, char *c_vals[], char *c_names[]);


/*****************************************************
 Process_lookup_results(): When a patient lookup query
  is executed there will be none, one, or multiple
  results. If no results, that is handled inside of
  Patient_lookup() above. If there are one or more results
  then if one result, this function assumes that the first
  result's enumerated identifier is the only possible
  selection and returns that. Otherwise, calls a function
  Lookup_result_selection() that allows the user to select
  the correct patient in the linked list datastructure
  and return it.

 RETURN: the number associated with the enumerated identifier
  of a patient object in the linked list data structure.

 *****************************************************/
int Process_lookup_results(PQ_node *n, char *last);

int Process_note_lookup_results(NQ_node *head, char *identifier);


/*****************************************************
 Create_add_user_query(): generates a simple string
  which is returned to a character pointer. This is
  used in an sqlite3 command to add a user to the
  database.
 *****************************************************/
char *Create_add_user_query(Patient *p);


/*****************************************************
 Create_patient_lookup_query(): generates a simple
  string which is returned to a character pointer. This
  is used in an sqlite3 query for looking up a patient
  in a databse.
 *****************************************************/
char *Create_patient_lookup_query(char *identifier, char *querymod);


/*****************************************************
 Create_add_note_query(): generates a simple string which
  is returned to a character pointer. This is used in an
  sqlite3 command to add a note to the database.
 *****************************************************/
char *Create_add_note_query(Note *n);


/*****************************************************
 PQ_node_alloc(): allocates heap space for a new
  Patient_query_node which will be integrated into a
  linked list.

 RETURN: returns pointer to position on heap.

 *****************************************************/
PQ_node *PQ_node_alloc(void);


/*****************************************************
 PQ_list_find_tail(): passed down-stream position of
  list and traverses until reaching a point here there
  is no next node. 

 RETURN: position of last node on list.

 *****************************************************/
PQ_node *PQ_list_find_tail(PQ_node *n);


/*****************************************************
 PQ_list_node_extract(): extracts a node from a linked
  list and returns it's position while re-attaching the
  prior list so there are no dangling pointers.

 RETURN: position on heap of extracted node.

 *****************************************************/
PQ_node *PQ_list_node_extract(PQ_node *n);


/*****************************************************
 PQ_node_add(): adds a new Patient_query_node to the
  linked list data structure.

 RETURN: true(1) for success false(0) for failure.

 *****************************************************/
BOOL PQ_node_add(PQ_node *n);


/*****************************************************
 PQ_list_pop(): pops, but does not return, tail of list.

 RETURN: true(1) for success false(0) for failure.

 *****************************************************/
BOOL PQ_list_pop(PQ_node *n);


/*****************************************************
 PQ_list_purge(): Takes head of a linked list of
  Patient_query_nodes and completes destroys it,
  including all patients.

 RETURN: true(1) for success false(0) for failure.

 *****************************************************/
BOOL PQ_list_purge(PQ_node *n);


/*****************************************************
 PQ_node_destroy(): destroys a single node from a list;
  this is probably somewhat redundant with PQ_list_pop
  and that should be addressed later.

 RETURN: true(1) for success false(0) for failure.

 *****************************************************/
BOOL PQ_node_destroy(PQ_node *n);


#endif

// eof: database.h

