// file: database.c
#include <string.h>
#include "database.h"


int Patient_demographics_table_create(sqlite3 *db)
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

    
    
  return rc;
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

char *Create_add_user_query(Patient *p)
{
  char *query = malloc(sizeof(char) * 1000);
  char day[2];
  sprintf(day, "%d", p->dob->day);
  char month[2];
  sprintf(month, "%d", p->dob->month);
  char year[4];
  sprintf(year, "%d", p->dob->year);

  query[0] = '\0';
  strcat(query, "INSERT INTO PATIENTS VALUES(");
  strcat(query, "NULL, '");
  strcat(query, p->name->first);
  strcat(query, "', '");
  strcat(query, p->name->middle);
  strcat(query, "', '");
  strcat(query, p->name->last);
  strcat(query, "', '");
  strcat(query, month);
  strcat(query, "', '");
  strcat(query, day);
  strcat(query, "', '");
  strcat(query, year);
  strcat(query, "', '");
  strcat(query, p->addr->field1);
  strcat(query, "', '");
  strcat(query, p->addr->field2);
  strcat(query, "', '");
  strcat(query, p->addr->field3);
  strcat(query, "', '");
  strcat(query, p->addr->field4);
  strcat(query, "', '");
  strcat(query, p->contact->phone_h);
  strcat(query, "', '");
  strcat(query, p->contact->phone_w);
  strcat(query, "', '");
  strcat(query, p->contact->phone_c);
  strcat(query, "', '");
  strcat(query, p->contact->email);
  strcat(query, "', '");
  strcat(query, p->emerg1->full_name);
  strcat(query, "', '");
  strcat(query, p->emerg1->relationship);
  strcat(query, "', '");
  strcat(query, p->emerg1->contact->phone_h);
  strcat(query, "', '");
  strcat(query, p->emerg1->contact->phone_w);
  strcat(query, "', '");
  strcat(query, p->emerg1->contact->phone_c);
  strcat(query, "', '");
  strcat(query, p->emerg1->contact->email);
  strcat(query, "', '");
  strcat(query, p->emerg2->full_name);
  strcat(query, "', '");
  strcat(query, p->emerg2->relationship);
  strcat(query, "', '");
  strcat(query, p->emerg2->contact->phone_h);
  strcat(query, "', '");
  strcat(query, p->emerg2->contact->phone_w);
  strcat(query, "', '");
  strcat(query, p->emerg2->contact->phone_c);
  strcat(query, "', '");
  strcat(query, p->emerg2->contact->email);
  strcat(query, "', '");
  strcat(query, p->pid);
  strcat(query, "');");

  return query;
}

Patient *Patient_lookup_last(char  *last, sqlite3 *db)
{
  Patient *pt = Patient_create();
  char sql[100];
  char *error = "Sqlite3 ERROR.";
  int rc;
  
  sql[0] = '\0';
  strcat(sql, "SELECT * FROM PATIENTS WHERE last = '");
  strcat(sql, last);
  strcat(sql, "';\0");

  // the 4th argument (pt) is provided to callback as the first
  // argument 'void *upd'. This is how we pass patient information
  // to a patient from the SQL query return.
  rc = sqlite3_exec(db, sql, Patient_find_callback, pt, &error);

  // do something with rc here
  if (rc == 0) rc = 0;
  
  return pt;
}

Patient *Patient_lookup_mrn(char  *mrn, sqlite3 *db)
{
  Patient *pt = Patient_create();
  char sql[100];
  char *error = "Sqlite3 ERROR.";
  int rc;
  
  sql[0] = '\0';
  strcat(sql, "SELECT * FROM PATIENTS WHERE mrn = '");
  strcat(sql, mrn);
  strcat(sql, "';\0");

  // the 4th argument (pt) is provided to callback as the first
  // argument 'void *upd'. This is how we pass patient information
  // to a patient from the SQL query return.
  rc = sqlite3_exec(db, sql, Patient_find_callback, pt, &error);

  // do something with rc here
  if (rc == 0) rc = 0;
  
  return pt;
}

Patient *Patient_lookup_first(char  *first, sqlite3 *db)
{
  Patient *pt = Patient_create();
  char sql[100];
  char *error = "Sqlite3 ERROR.";
  int rc;
  
  sql[0] = '\0';
  strcat(sql, "SELECT * FROM PATIENTS WHERE first = '");
  strcat(sql, first);
  strcat(sql, "';\0");

  // the 4th argument (pt) is provided to callback as the first
  // argument 'void *upd'. This is how we pass patient information
  // to a patient from the SQL query return.
  rc = sqlite3_exec(db, sql, Patient_find_callback, pt, &error);

  // do something with rc here
  if (rc == 0) rc = 0;
  
  return pt;
}

static int Patient_find_callback(void *udp, int c_num, char *c_vals[], char *c_names[])
{
  
  strcpy(((Patient*)udp)->mrn, c_vals[0]);
  strcpy(((Patient*)udp)->name->first, c_vals[1]);
  strcpy(((Patient*)udp)->name->middle, c_vals[2]);
  strcpy(((Patient*)udp)->name->last, c_vals[3]);
  ((Patient*)udp)->dob->month = atoi(c_vals[4]);
  ((Patient*)udp)->dob->day = atoi(c_vals[5]);
  ((Patient*)udp)->dob->year = atoi(c_vals[6]);
  strcpy(((Patient*)udp)->addr->field1, c_vals[7]);
  strcpy(((Patient*)udp)->addr->field2, c_vals[8]);
  strcpy(((Patient*)udp)->addr->field3, c_vals[9]);
  strcpy(((Patient*)udp)->addr->field4, c_vals[10]);
  strcpy(((Patient*)udp)->contact->phone_h, c_vals[11]);
  strcpy(((Patient*)udp)->contact->phone_w, c_vals[12]);
  strcpy(((Patient*)udp)->contact->phone_c, c_vals[13]);
  strcpy(((Patient*)udp)->contact->email, c_vals[14]);
  strcpy(((Patient*)udp)->emerg1->full_name, c_vals[15]);
  strcpy(((Patient*)udp)->emerg1->relationship, c_vals[16]);
  strcpy(((Patient*)udp)->emerg1->contact->phone_h, c_vals[17]);
  strcpy(((Patient*)udp)->emerg1->contact->phone_w, c_vals[18]);
  strcpy(((Patient*)udp)->emerg1->contact->phone_c, c_vals[19]);
  strcpy(((Patient*)udp)->emerg1->contact->email, c_vals[20]);
  strcpy(((Patient*)udp)->emerg2->full_name, c_vals[21]);
  strcpy(((Patient*)udp)->emerg2->relationship, c_vals[22]);
  strcpy(((Patient*)udp)->emerg2->contact->phone_h, c_vals[23]);
  strcpy(((Patient*)udp)->emerg2->contact->phone_w, c_vals[24]);
  strcpy(((Patient*)udp)->emerg2->contact->phone_c, c_vals[25]);
  strcpy(((Patient*)udp)->emerg2->contact->email, c_vals[26]);
  strcpy(((Patient*)udp)->pid, c_vals[27]);

  return 0;
}

// eof: database.c
