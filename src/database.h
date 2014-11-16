// file: database.h

#ifndef _database_h
#define _database_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "patient.h"
#include "database.h"

int Patient_demographics_table_create(sqlite3 *db);
void Database_validate(int rc);
char *Create_add_user_query(Patient *p);
Patient *Patient_lookup_mrn(char  *mrn, sqlite3 *db);
static int Patient_find_callback(void *upd, int num_c, char *c_vals[], char *c_names[]);
//Patient *Patient_lookup_last(char *last);
//Patient *Patient_lookup_first(char *first);

#endif

// eof: database.h
