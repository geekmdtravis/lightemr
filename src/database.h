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

#endif

// eof: database.h
