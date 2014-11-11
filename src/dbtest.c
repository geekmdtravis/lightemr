// file: dbtest.c

// TO DO: resolve issue where I need to input 28 (not 27) values
// the problem is that the first value is an auto-incrementing value.
// perhaps just specifying accepting values is the only fix?

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "patient.h"
#include "database.h"

int Table_create(sqlite3 *db);
void Database_validate(int rc);
void Patient_data_input(Patient *p);
char *Create_add_user_query(Patient *p);

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

  Table_create(db);

  rq = Create_add_user_query(p);
  strcpy(sql, rq);
  printf("%s\n%s\n", sql, rq);
  rc = sqlite3_exec(db, sql, NULL, 0, &error);
  free(rq);
  
  sqlite3_close(db);

  exit(EXIT_SUCCESS);
}

int Table_create(sqlite3 *db)
{
  int rc;
  char *error = "ERROR";
  
  char *sql = "CREATE TABLE PATIENTS(" \
    "MRN INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, " \
    "FIRST CHAR(40) NOT NULL, " \
    "MIDDLE CHAR(40), " \
    "LAST CHAR(40) NOT NULL, " \
    "MONTH INT NOT NULL, " \
    "DAY INT NOT NULL, " \
    "YEAR INT NOT NULL, " \
    "ADDR_F1 CHAR(50) NOT NULL, " \
    "ADDR_F2 CHAR(50) NOT NULL, " \
    "ADDR_F3 CHAR(50) NOT NULL, " \
    "ADDR_F4 CHAR(50) NOT NULL, " \
    "PHONE_H CHAR(40), " \
    "PHONE_C CHAR(40), " \
    "PHONE_W CHAR(40), " \
    "EMAIL CHAR(50), " \
    "EC1_FULLNAME CHAR(80) NOT NULL, " \
    "EC1_RELATIONSHIP CHAR(100) NOT NULL, " \
    "EC1_PHONE_H CHAR(40), " \
    "EC1_PHONE_W CHAR(40), " \
    "EC1_PHONE_C CHAR(40), " \
    "EC1_EMAIL CHAR(50), " \
    "EC2_FULLNAME CHAR(80) NOT NULL, " \
    "EC2_RELATIONSHIP CHAR(100) NOT NULL, " \
    "EC2_PHONE_H CHAR(40), " \
    "EC2_PHONE_W CHAR(40), " \
    "EC2_PHONE_C CHAR(40), " \
    "EC2_EMAIL CHAR(50), " \
    "PID CHAR(40)" \
    ");";

  rc = sqlite3_exec(db, sql, NULL, 0, &error);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL Error: %s\n", error);
  } else {
    fprintf(stdout, "Table created.\n");
  }
  
    
    
  return 0;
}

void Database_validate(int rc)
{
  #define RETURN_SUCCESS 0
  
  if(rc == RETURN_SUCCESS) {
    fprintf(stdout, "Opened database successfully.\n");
  } else {
    fprintf(stderr, "Could not open database.\n");
  }
}

void Patient_data_input(Patient *p)
{
  p->init = Patient_populate;
  Name n = {.first = "Travis", .middle = "Robert", .last = "Nesbit" };
  Birthdate b = {.month = 6, .day = 29, .year = 1983};
  Address a = {.field1 = "field1",
	       .field2 = "field2",
	       .field3 = "field3",
	       .field4 = "field4" };
  Contact c = {.phone_h = "9518138895", .phone_c = "9518138895",
	       .phone_w = "7144567890", .email = "tnesbit450ATgmail.com" };
  Emergency_contact ec1 = { .full_name = "Jennifer T. Baker-Nesbit",
			   .relationship = "Wife",
			   .contact.phone_h = "9512970019",
			   .contact.phone_c = "9512970019",
			   .contact.phone_w = "",
			   .contact.email = "cashewsmamaATgmail.com" };
   Emergency_contact ec2 = { .full_name = "Jennifer T. Baker-Nesbit",
			   .relationship = "Wife",
			   .contact.phone_h = "9512970019",
			   .contact.phone_c = "9512970019",
			   .contact.phone_w = "",
			   .contact.email = "cashewsmama@gmail.com" };
   p->init(p, &n, &b, &a, &c, &ec1, &ec2, "111222333", "1234567890");
  
}

char *Create_add_user_query(Patient *p)
{
  char *query = malloc(sizeof(char) * 1000);
  char day[2];
  sprintf(day, "%d", p->dob.day);
  char month[2];
  sprintf(month, "%d", p->dob.month);
  char year[4];
  sprintf(year, "%d", p->dob.year);

  query[0] = '\0';
  strcat(query, "INSERT INTO PATIENTS VALUES('");
  strcat(query, p->name.first);
  strcat(query, "', '");
  strcat(query, p->name.middle);
  strcat(query, "', '");
  strcat(query, p->name.last);
  strcat(query, "', '");
  strcat(query, month);
  strcat(query, "', '");
  strcat(query, day);
  strcat(query, "', '");
  strcat(query, year);
  strcat(query, "', '");
  strcat(query, p->addr.field1);
  strcat(query, "', '");
  strcat(query, p->addr.field2);
  strcat(query, "', '");
  strcat(query, p->addr.field3);
  strcat(query, "', '");
  strcat(query, p->addr.field4);
  strcat(query, "', '");
  strcat(query, p->contact.phone_h);
  strcat(query, "', '");
  strcat(query, p->contact.phone_w);
  strcat(query, "', '");
  strcat(query, p->contact.phone_c);
  strcat(query, "', '");
  strcat(query, p->contact.email);
  strcat(query, "', '");
  strcat(query, p->emerg1.full_name);
  strcat(query, "', '");
  strcat(query, p->emerg1.relationship);
  strcat(query, "', '");
  strcat(query, p->emerg1.contact.phone_h);
  strcat(query, "', '");
  strcat(query, p->emerg1.contact.phone_w);
  strcat(query, "', '");
  strcat(query, p->emerg1.contact.phone_c);
  strcat(query, "', '");
  strcat(query, p->emerg1.contact.email);
  strcat(query, "', '");
  strcat(query, p->emerg2.full_name);
  strcat(query, "', '");
  strcat(query, p->emerg2.relationship);
  strcat(query, "', '");
  strcat(query, p->emerg2.contact.phone_h);
  strcat(query, "', '");
  strcat(query, p->emerg2.contact.phone_w);
  strcat(query, "', '");
  strcat(query, p->emerg2.contact.phone_c);
  strcat(query, "', '");
  strcat(query, p->emerg2.contact.email);
  strcat(query, "', '");
  strcat(query, p->pid);
  strcat(query, "');");

  return query;
}

// eof: dbtest.c
