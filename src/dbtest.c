// file: dbtest.c

// TO DO: resolve issue where I need to input 28 (not 27) values
// the problem is that the first value is an auto-incrementing value.
// perhaps just specifying accepting values is the only fix?

#include "database.h"

void Patient_data_input(Patient *p);

int main()
{
  Patient *p = Patient_create();
  sqlite3 *db;
  char *error = "Sqlite3 ERROR.";
  char sql[1000];
  char *rq;
  int rc;

  Patient_data_input(p);
  // Patient_print_info(p);

  rc = sqlite3_open("patient.db", &db);
  Database_validate(rc);

  Patient_demographics_table_create(db);

  rq = Create_add_user_query(p);
  strcpy(sql, rq);
  free(rq);
  rc = sqlite3_exec(db, sql, NULL, 0, &error);
  
  sqlite3_close(db);

  exit(EXIT_SUCCESS);
}



void Patient_data_input(Patient *p)
{
  p->init = Patient_populate;
  Name n = {.first = "Travis", .middle = "Robert", .last = "Nesbit" };
  Birthdate b = {.month = 6, .day = 29, .year = 1983};
  Address a = {.field1 = "1 Glenhurst",
	       .field2 = "Irvine, CA",
	       .field3 = "92604-1234",
	       .field4 = "United States of America" };
  Contact c = {.phone_h = "9518138895", .phone_c = "9518138895",
	       .phone_w = "7144567890", .email = "tnesbit450@gmail.com" };
  Emergency_contact ec1 = { .full_name = "Jennifer T. Baker-Nesbit",
			   .relationship = "Wife",
			   .contact.phone_h = "9512970019",
			   .contact.phone_c = "",
			   .contact.phone_w = "",
			   .contact.email = "cashewsmama@gmail.com" };
  Emergency_contact ec2 = { .full_name = "Mary E. Nesbit-Houx",
			   .relationship = "Mother",
			   .contact.phone_h = "9516955456",
			   .contact.phone_c = "",
			   .contact.phone_w = "",
			   .contact.email = "mary.houx@gmail.com" };
   p->init(p, &n, &b, &a, &c, &ec1, &ec2, "111222333", "1234567890");
  
}


// eof: dbtest.c
