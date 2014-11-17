// file: dbtest.c

// TO DO: resolve issue where I need to input 28 (not 27) values
// the problem is that the first value is an auto-incrementing value.
// perhaps just specifying accepting values is the only fix?

#include "database.h"
#include "dbg.h"

void Patient_data_input(Patient *p);

int main()
{
  Patient *p = Patient_create();
  sqlite3 *db;
  char *error = "Sqlite3 ERROR.";
  char sql[1000];
  char *rq;
  int rc;

  // Populate quickly with sample data
  Patient_data_input(p);

  // Open and validate databse
  rc = sqlite3_open("patient.db", &db);
  Database_validate(rc);

  // Create the table
  Patient_demographics_table_create(db);

  // Create the add user query for above patient
  // and execute the query.
  rq = Create_add_user_query(p);
  strcpy(sql, rq);
  free(rq);
  rc = sqlite3_exec(db, sql, NULL, 0, &error);

  // Destroy the patient that was created
  // and lookup a new one
  Patient_destroy(p);
  p = Patient_lookup_mrn("1", db);
  Patient_print_info(p);

  // same but by last name
  Patient_destroy(p);
  p = Patient_lookup_last("Nesbit", db);
  Patient_print_info(p);

  // same but by first name
  Patient_destroy(p);
  p = Patient_lookup_first("Travis", db);
  Patient_print_info(p);

  // final patient object destroy
  Patient_destroy(p);

  // close the database
  sqlite3_close(db);

  exit(EXIT_SUCCESS);
}


void Patient_data_input(Patient *p)
{
  int rc;
  
  rc = Patient_update_name(p, "Travis", "Robert", "Nesbit");
  rc = Patient_update_address(p, "1 Glenhurst", "Irvine, CA", "92604", "USA");
  rc = Patient_update_dob(p, 6, 29, 1983);
  rc = Patient_update_contact(p, "951.813.8895", "", "", "tnesbit450@gmail.com");
  rc = Patient_update_emergency(p->emerg1, "Jennifer T. Baker-Nesbit", "951.297.0019",
				"", "", "Wife", "cashewsmama@gmail.com");
  rc = Patient_update_emergency(p->emerg2, "Mary E. Nesbit-Houx", "951.695.5456",
				"", "", "Mother", "mary.houx@gmail.com");
}


// eof: dbtest.c
