#include <stdio.h>
#include <string.h>
#include "note.h"
#include "database.h"

int main()
{
  Note *n = Note_create("1");
  char *query;
  char *error;
  sqlite3 *db;
  int rc;

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

  query  = Create_add_note_query(n);
	 

  rc = sqlite3_open("lightemr.data", &db); 

  sqlite3_exec(db, query, NULL, NULL, &error);

  Note_destroy(n);
  free(query);
  
  return 0;
}
