// file: database.c
#include <string.h>
#include "database.h"
#include "defs.h"

/********************************************************
 ********************************************************
          NOTES TABLE AND LOOKUP
 ********************************************************
 *******************************************************/
// Generate an SQL command to create a table with
// fields mrn, title, author, time, replaced, and text.
// NOTE: the 'replaced' field is meant to effectively
// rended a field deactivated. There will be no
// updates to notes. They will only be replaced with
// new notes.
int Patient_notes_table_create(sqlite3 *db)
{
  int rc;
  char *error = "ERROR";

  char *sql = "CREATE TABLE NOTES(" \
    "MRN INTEGER NOT NULL," \
    "TITLE CHAR(50) NOT NULL, " \
    "AUTHOR CHAR(80) NOT NULL, " \
    "TIME INTEGER NOT NULL, " \
    "REPLACED INTEGER NOT NULL, " \
    "TEXT CHAR(8000)" \
    ");";

  rc = sqlite3_exec(db, sql, NULL, NULL, &error);

  // The input and output here would likely benefit
  // from development of a 'log' rather than sending this
  // to stdout/stderr.
  if(rc != SQLITE_OK) {
    fprintf(stderr, "SQL Error: %s\n", error);
  } else {
    fprintf(stdout, "Table created.\n");
  }

  // Clean up the sqlite3 query/command
  sqlite3_free(error);

  // Return the sqlite3_exec return value
  return rc;
}

char *Create_add_note_query(const Note *n)
{
  // Allocate memory on heap for the query we're
  // returning as a string.
  char *query = malloc(sizeof(char) * MAX_QUERY);
  

  return query;
}


/********************************************************
 ********************************************************
       PATIENT DEMOGRAPHICS TABLE AND LOOKUP
 ********************************************************
 *******************************************************/
// Create a sqlite statement which creates a table
// containing all fields from the "Patient" struct.
int Patient_demographics_table_create(sqlite3 *db)
{
  int rc;
  char *error = "ERROR";

  // The SQL statement to add patient 'p' to database
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

  // Execute the query
  rc = sqlite3_exec(db, sql, NULL, NULL, &error);

  // To do: send to a log instead of stderr/stdout
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL Error: %s\n", error);
  } else {
    fprintf(stdout, "Table created.\n");
  }

  // Clean up the sqlite query/statement
  sqlite3_free(error);
  
  return rc;
}

// Create a statement for adding patient 'p' to
// the database.
char *Create_add_user_query(const Patient *p)
{
  // Allocate heap memory
  char *query = malloc(sizeof(char) * MAX_QUERY);
  
  // Turn the day / mo / year values into strings
  // so they can be placed into the statement
  char day[2]; sprintf(day, "%d", p->dob->day);
  char month[2]; sprintf(month, "%d", p->dob->month);
  char year[4]; sprintf(year, "%d", p->dob->year);

  // Before we concatenate, make sure there is a null
  // terminating character which can be recognized by the
  // strcat function
  query[0] = '\0';
  // Generate the statement
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
// Generate a query that will allow us to lookup a
// patient by the query provided.
// RETURN: return's a pointer to a Patient object on the heap
Patient *Patient_lookup(sqlite3 *db, const char *identifier, const char *querymod)
{
  // The PQR struct was created specifically to deal with the
  // callback function in the patient_lookup_ functions. For
  // more details, see database.h where the definition of this
  // structure is. PQR is a typedef for the following struct:
  // typedef struct Patient_query_result {
  //    Patient *resultList[MAX_RESULTS];
  //    int count;
  // } PQR;
  PQR pqr;
  Patient *pt;
  char sql[100];
  char *error = "Sqlite3 ERROR.";
  int rc, i, selection;

  // Initialize the patient list for up to MAX_RESULTS patients.
  for(i = 0; i < MAX_RESULTS; i++) {
    pqr.resultList[i] = Patient_create();
  }

  // Create the query
  sql[0] = '\0';
  strcat(sql, "SELECT * FROM PATIENTS WHERE LOWER(");
  strcat(sql, querymod);
  strcat(sql, ") = LOWER('");
  strcat(sql, identifier);
  strcat(sql, "');\0");

  // Set the pqr.count value to zero to indicate that the callback
  // function has not yet been invoked.
  pqr.count = 0;
  // Execute the query on 'db' with query 'sql' invoking callback
  // 'Patient_find_callback' and passing a pointer to the struct
  // 'pqr' which contains the patient list and a counter for the
  // callbacks and error message 'error'.
  // NOTE: emphasis on pointer &pqr being passed to this fourth
  // argument position, which ultimately is passed on further
  // to the void poitner 'void *udp' in the callback function
  rc = sqlite3_exec(db, sql, Patient_find_callback, &pqr, &error);
  // Assign an integer value identifiing the correct patient to
  // selection and then assign that result to patient. Do this
  // so long as the selection returned is valid
  selection = Patient_select(&pqr, identifier);
  if (selection != -1) {
    pt = pqr.resultList[selection];
  } else {
    pt = NULL;
  }
  
  // If the result of the query is a blank patient, destroy it.
  if (pt && (strcmp(pt->mrn, "") == 0 || rc != SQLITE_OK)) Patient_destroy(pt);

  // Destroy all patients returned and all blank patients on the heap
  // except the one user has selected
  for(i = 0; i < MAX_RESULTS; i++) {
    if(pqr.resultList[i] && i != selection) Patient_destroy(pqr.resultList[i]);
  }

  // Cleanup the sqlite3 error message
  sqlite3_free(error);
  
  return pt;
}

// This function is executed inside of sql3_exec for EACH row in the
// database. c_num is the number of columns, *c_vals[] is a pointer
// to a list of 'c_num' values as extracted from columns in that row
// and *c_names[] is a similar list but which represents the names
// for the column headers.
// RETURN: 0 for success, -1 for failure to get patient from database
int Patient_find_callback(void *udp, int c_num, char *c_vals[], char *c_names[])
{
  // For clarity in the code assign 'i'.
  int i = ((PQR*)udp)->count;

  // Copy the values from each column into their respective
  // fields in the PQR.resultList[i] Patient object on the heap
  strcpy(((PQR*)udp)->resultList[i]->mrn, c_vals[0]);
  strcpy(((PQR*)udp)->resultList[i]->name->first, c_vals[1]);
  strcpy(((PQR*)udp)->resultList[i]->name->middle, c_vals[2]);
  strcpy(((PQR*)udp)->resultList[i]->name->last, c_vals[3]);
  // Recall: mo/day/yr are ints
  ((PQR*)udp)->resultList[i]->dob->month = atoi(c_vals[4]);
  ((PQR*)udp)->resultList[i]->dob->day = atoi(c_vals[5]);
  ((PQR*)udp)->resultList[i]->dob->year = atoi(c_vals[6]);
  strcpy(((PQR*)udp)->resultList[i]->addr->field1, c_vals[7]);
  strcpy(((PQR*)udp)->resultList[i]->addr->field2, c_vals[8]);
  strcpy(((PQR*)udp)->resultList[i]->addr->field3, c_vals[9]);
  strcpy(((PQR*)udp)->resultList[i]->addr->field4, c_vals[10]);
  strcpy(((PQR*)udp)->resultList[i]->contact->phone_h, c_vals[11]);
  strcpy(((PQR*)udp)->resultList[i]->contact->phone_w, c_vals[12]);
  strcpy(((PQR*)udp)->resultList[i]->contact->phone_c, c_vals[13]);
  strcpy(((PQR*)udp)->resultList[i]->contact->email, c_vals[14]);
  strcpy(((PQR*)udp)->resultList[i]->emerg1->full_name, c_vals[15]);
  strcpy(((PQR*)udp)->resultList[i]->emerg1->relationship, c_vals[16]);
  strcpy(((PQR*)udp)->resultList[i]->emerg1->contact->phone_h, c_vals[17]);
  strcpy(((PQR*)udp)->resultList[i]->emerg1->contact->phone_w, c_vals[18]);
  strcpy(((PQR*)udp)->resultList[i]->emerg1->contact->phone_c, c_vals[19]);
  strcpy(((PQR*)udp)->resultList[i]->emerg1->contact->email, c_vals[20]);
  strcpy(((PQR*)udp)->resultList[i]->emerg2->full_name, c_vals[21]);
  strcpy(((PQR*)udp)->resultList[i]->emerg2->relationship, c_vals[22]);
  strcpy(((PQR*)udp)->resultList[i]->emerg2->contact->phone_h, c_vals[23]);
  strcpy(((PQR*)udp)->resultList[i]->emerg2->contact->phone_w, c_vals[24]);
  strcpy(((PQR*)udp)->resultList[i]->emerg2->contact->phone_c, c_vals[25]);
  strcpy(((PQR*)udp)->resultList[i]->emerg2->contact->email, c_vals[26]);
  strcpy(((PQR*)udp)->resultList[i]->pid, c_vals[27]);

  // Increment the count so we know how many patients are returned to the list
  // and so that we can assign the next patient to the next list position
  ((PQR*)udp)->count++;

  // If the mrn isn't blank, return 0 for success otherwise -1 
  return (strcmp(((PQR*)udp)->resultList[i]->mrn, "") == 0 ? -1 : 0);
}

// When multiple results are passed back to the PQR by multiple executions
// of the patient callback, this function is used to allow the user to
// discriminate between them and select their intended patient from that
// list of candidates.
// RETURN: returns an integer which is associated with the position of the
// pointer to the Patient of interest in the array of the Patient object
// pointers.
int Patient_select(const struct Patient_query_result *pqr, const char *querymod)
{
  int selection, i, j;
  size_t nbytes = 4;
  void (*prt)(char *input, int align) = Print_interface_line;
  char ptResult[MAX_LINE_TEXT];


  // If there is only one returned patient, we know that patient is going
  // to be found in array index zero (0).
  if(pqr->count == 1) {
    selection = 0;
  } else if (pqr->count < 1) {
    return -1;
  } else { // Otherwise
    system("clear");
    prt(THIN_LINE, LEFT);
    prt("LightEMR: Lookup Patient", CENTER);
    prt(THICK_LINE, LEFT);
    prt("Multiple results returned. Select desired patient.", CENTER);
    prt(THIN_LINE, LEFT);

    // Print each of the candidates along with an integer value
    // which correlates with it's array index position.
    for (i = 0; i < pqr->count; i++) {
      // Null out the ptResult
      for (j = 0; j < MAX_LINE_TEXT; j++) ptResult[j] = '\0';
      sprintf(ptResult, "[ # %d][ %s %s %s MRN: %s DOB %d/%d/%d ] ",
	     i,
	     pqr->resultList[i]->name->first,
	     pqr->resultList[i]->name->middle,
	     pqr->resultList[i]->name->last,
	     pqr->resultList[i]->mrn,
	     pqr->resultList[i]->dob->month,
	     pqr->resultList[i]->dob->day,
	     pqr->resultList[i]->dob->year);
      prt(ptResult, LEFT);
    }
    prt(BLANK_LINE, LEFT);
    prt(THIN_LINE, LEFT);
    // Record that position
    fprintf(stdout, SELECTION_PROMPT_LONG);
    modgetlatoi(&selection, &nbytes);
  }

  // return that position as selection so long as it's a valid
  // selection value
  return (selection <= pqr->count) ? selection : -1;
}
// eof: database.c
