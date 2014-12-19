#include <stdio.h>
#include <string.h>
#include "note.h"
#include "database.h"
#include "patient.h"

Note *Note_lookup(sqlite3 *db, char *identifier, char *field);
char *Create_note_lookup_query(char *identifier, char *field);

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

  // Destroy the old note
  if(n) Note_destroy(n); n = NULL;

  // Lookup the note from the database
  n = Note_lookup(db, "1", "MRN");

  if(error) sqlite3_free(error); error = NULL;
  if(query) free(query); query = NULL;
  if(n) Note_destroy(n); n = NULL;
  if(db) sqlite3_close(db); db = NULL;
  
  return 0;
}

Note *Note_lookup(sqlite3 *db, char *identifier, char *field)
{
  Note *n = NULL;
  char *sqlQuery = Create_note_lookup_query(identifier, field);
  char *error = NULL;
  int rc;

  rc = sqlite3_exec(db, sqlQuery, NULL, NULL, &error);
  if(sqlQuery) free(sqlQuery); sqlQuery = NULL;
  if(error) sqlite3_free(error); error = NULL;

  return n;
}

char *Create_note_lookup_query(char *identifier, char *field)
{
  char *query = malloc(sizeof(char) * MAX_QUERY);
  int i;
  // Empty out the query string with null terms
  for (i = 0; i < MAX_QUERY; ++i) query[i] = '\0';

  // SELECT * FROM NOTES WHERE LOWER("MRN") = LOWER("1"); 
  strcat(query, "SELECT * FROM PATIENTS WHERE LOWER(\"");
  strcat(query, field);
  strcat(query, "\") = LOWER(\"");
  strcat(query, identifier);
  strcat(query, "\");");	 
  
  return query;
}
