#include <stdio.h>
#include <string.h>
#include "note.h"
#include "database.h"
#include "patient.h"


int main()
{
  Note *n = Note_create("1");
  char *query = NULL;
  char *error = NULL;
  sqlite3 *db;
  int rc = 0;

  // Create a note
  strcat(n->title, "History and Physical");
  strcat(n->author, "Dr. Super Awesome");
  strcat(n->text,
	 "S: This is a 40 yr M with "
	 "DM2 here for follow up on his "
	 "insulin regimen. He has good "
	 "sugar control.\n\n"
	 "O: \n"
	 "Physical exam: \n"
	 "AAOx4, NC/AT, RRR, +BS, NT/ND\n\n"
	 "Plan:\n"
	 "# DM2: Good control\n"
	 "- continue januvia\n\0");
  // Create a note  ADD query
  query  = Create_add_note_query(n);

  // Add a note to the database
  rc = sqlite3_open("lightemr.data", &db); 
  sqlite3_exec(db, query, NULL, NULL, &error);

  // Destroy the old note, close, and reopen database
  // to recieve updates
  if(n) Note_destroy(n); n = NULL;
  sqlite3_close(db);
  db = NULL;
  rc = sqlite3_open("lightemr.data", &db); 

  // Lookup the note from the database
  n = Note_lookup(db, "1", "MRN");

  // Print the results of the lookup
  if(n) {
    fprintf(stdout,
	    "Patient MRN: %s\n"
	    "Author: %s     Title : %s\n     Time  : %s\n"
	    "Note contents\n"
	    "=============\n"
	    "%s\n",
	    n->mrn,
	    n->author,
	    n->title,
	    n->time,
	    n->text);
  }
  // Cleanup and exit
  if(error) sqlite3_free(error); error = NULL;
  if(query) free(query); query = NULL;
  if(n) Note_destroy(n); n = NULL;
  if(db) sqlite3_close(db); db = NULL;
  
  return 0;
}
