// file: database.c

#include "database.h"

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
    "TIME CHAR(40) NOT NULL, " \
    "TIME_SEC INTEGER NOT NULL, " \
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

char *Create_add_note_query(Note *n)
{
  // Allocate memory on heap for the query we're
  // returning as a string.
  char *query = malloc(sizeof(char) * MAX_QUERY);
  char timeStr[MAX_DATA];
  int i;
  
  CLEAR_STRING(query, i, MAX_QUERY);
  strcat(query, "INSERT INTO NOTES VALUES('");
  strcat(query, n->mrn);
  strcat(query, "', '");
  strcat(query, n->title);
  strcat(query, "', '");
  strcat(query, n->author);
  strcat(query, "', '");
  strcat(query, n->time);
  strcat(query, "', '");
  CLEAR_STRING(timeStr, i, MAX_DATA);
  sprintf(timeStr, "%lld",(long long)n->time_sec);
  strcat(query, timeStr);
  strcat(query, "', '");
  strcat(query, n->replaced);
  strcat(query, "', '");
  strcat(query, n->text);
  strcat(query, "');");

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
char *Create_add_user_query(Patient *p)
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
///////////////////////////////////////////////////////////////////
// Patient_lookup()                                             ///
///////////////////////////////////////////////////////////////////
// Generate a query that will allow us to lookup a
// patient by the query provided.
// RETURN: return's a pointer to a Patient object on the heap
///////////////////////////////////////////////////////////////////
Patient *Patient_lookup(sqlite3 *db, char *identifier, char *querymod)
{
  PQ_node *p_head = PQ_node_alloc();
  PQ_node *p_tmp = NULL;
  Patient *p_pt = NULL;
  char *sqlQuery = NULL;
  char *error = "Sqlite3 ERROR.";
  int rc, selection;

  // Create query, run query, free sqlQuery from mem when done
  sqlQuery = Create_patient_lookup_query(identifier, querymod);
  rc = sqlite3_exec(db, sqlQuery, Patient_find_callback, p_head, &error);
  free(sqlQuery);
  sqlite3_free(error); // cleanup the sqlite3 error message

  // Remove the dummy patient that is returned with each patient_find_callback
  // If there is no 'next', then no dummy was returned, and likely there is
  // an error so list is purged and null returned.
  if(p_head->next && rc == SQLITE_OK) {
    PQ_list_pop(p_head);
  } else {
    PQ_list_purge(p_head);
    p_pt = NULL;
    return p_pt;
  }

  // Get the users selection of correct patient
  selection = Patient_select(p_head, querymod);

  // if patient is found by list, as identified by selection #, then
  // copy it to new pt before destroying returned list.
  for(p_tmp = p_head; p_tmp->next; p_tmp = p_tmp->next) {
    if(p_tmp->count == selection && p_tmp->pt) p_pt = Patient_copy(p_tmp->pt);
  }
  if(p_tmp->count == selection && p_tmp->pt) p_pt = Patient_copy(p_tmp->pt);

  // Destroy the linked list of patients (a PQ_node)
  PQ_list_purge(p_head);
    
  return p_pt;
}


char *Create_patient_lookup_query(char *identifier, char *querymod)
{
  char *sql = malloc(sizeof(char) * MAX_QUERY);
  
  // Create the query
  sql[0] = '\0';
  strcat(sql, "SELECT * FROM PATIENTS WHERE LOWER(");
  strcat(sql, querymod);
  strcat(sql, ") = LOWER('");
  strcat(sql, identifier);
  strcat(sql, "');\0");

  return sql;
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
  // int i = ((PQR*)udp)->count;
  PQ_node *tail = PQ_list_find_tail((PQ_node*)udp);

  // Copy the values from each column into their respective
  // fields in the PQR.resultList[i] Patient object on the heap
  strcpy(tail->pt->mrn, c_vals[0]);
  strcpy(tail->pt->name->first, c_vals[1]);
  tail->pt->name->first[0] = toupper(tail->pt->name->first[0]);
  strcpy(tail->pt->name->middle, c_vals[2]);
  tail->pt->name->middle[0] = toupper(tail->pt->name->middle[0]);
  strcpy(tail->pt->name->last, c_vals[3]);
  tail->pt->name->last[0] = toupper(tail->pt->name->last[0]);
  // Recall: mo/day/yr are ints
  tail->pt->dob->month = atoi(c_vals[4]);
  tail->pt->dob->day = atoi(c_vals[5]);
  tail->pt->dob->year = atoi(c_vals[6]);
  strcpy(tail->pt->addr->field1, c_vals[7]);
  strcpy(tail->pt->addr->field2, c_vals[8]);
  strcpy(tail->pt->addr->field3, c_vals[9]);
  strcpy(tail->pt->addr->field4, c_vals[10]);
  strcpy(tail->pt->contact->phone_h, c_vals[11]);
  strcpy(tail->pt->contact->phone_w, c_vals[12]);
  strcpy(tail->pt->contact->phone_c, c_vals[13]);
  strcpy(tail->pt->contact->email, c_vals[14]);
  strcpy(tail->pt->emerg1->full_name, c_vals[15]);
  strcpy(tail->pt->emerg1->relationship, c_vals[16]);
  strcpy(tail->pt->emerg1->contact->phone_h, c_vals[17]);
  strcpy(tail->pt->emerg1->contact->phone_w, c_vals[18]);
  strcpy(tail->pt->emerg1->contact->phone_c, c_vals[19]);
  strcpy(tail->pt->emerg1->contact->email, c_vals[20]);
  strcpy(tail->pt->emerg2->full_name, c_vals[21]);
  strcpy(tail->pt->emerg2->relationship, c_vals[22]);
  strcpy(tail->pt->emerg2->contact->phone_h, c_vals[23]);
  strcpy(tail->pt->emerg2->contact->phone_w, c_vals[24]);
  strcpy(tail->pt->emerg2->contact->phone_c, c_vals[25]);
  strcpy(tail->pt->emerg2->contact->email, c_vals[26]);
  strcpy(tail->pt->pid, c_vals[27]);

  PQ_node_add(tail);
  
  // Increment the count so we know how many patients are returned to the list
  // and so that we can assign the next patient to the next list position
  // ((PQR*)udp)->count++;

  // If the mrn isn't blank, return 0 for success otherwise -1 
  return (strcmp(((PQ_node*)udp)->pt->mrn, "") == 0 ? -1 : 0);
}

// When multiple results are passed back to the PQR by multiple executions
// of the patient callback, this function is used to allow the user to
// discriminate between them and select their intended patient from that
// list of candidates.
// RETURN: returns an integer which is associated with the position of the
// pointer to the Patient of interest in the array of the Patient object
// pointers.
// change name to: Lookup results processing
int Patient_select(PQ_node *head, char *querymod)
{
  int selection;
  PQ_node *tail = PQ_list_find_tail(head);

  if (tail == head) {
    selection = head->count;
    head->selected = TRUE;
  } else {
    selection = Lookup_result_selection(head);
  }

  return selection;
}
// eof: database.c

/**************************************************
 Patient query results linked list will be implem-
 ented through these function.
 **************************************************/
PQ_node *PQ_node_alloc(void) {
  
  PQ_node *n = malloc(sizeof(PQ_node));
  n->next = NULL;
  n->prev = NULL;
  n->count = 1;
  n->selected = FALSE;

  n->pt = Patient_create();
  
  return n;
}

BOOL PQ_node_add(PQ_node *n) {
  PQ_node *new = PQ_node_alloc();
  PQ_node *tail = PQ_list_find_tail(n);

  tail->next = new;
  new->prev = tail;
  new->count = tail->count + 1;

  return ((new) ? TRUE : FALSE);
}

BOOL PQ_list_pop(PQ_node *n)
{
  PQ_node *tail = PQ_list_find_tail(n);
  PQ_node *newTail = tail->prev;

  if(tail->pt) {
    Patient_destroy(tail->pt);
    tail->pt = NULL;
  } else {
    return FALSE;
  }
  if (tail) {
    free(tail);
    tail = NULL;
  } else {
    return FALSE;
  }
  if (newTail) {
    newTail->next = NULL;
  }
  
  return TRUE;
}

PQ_node *PQ_list_find_tail(PQ_node *n)
{
  PQ_node *tail;

  for(tail = n; tail->next; tail = tail->next);

  return tail;
}

void PQ_list_purge(PQ_node *n)
{
  PQ_node *p_head = n;
  PQ_node *p_next = NULL;
  PQ_node *p_curr = NULL;

  p_curr = p_head;
  while(p_curr->next){
    if(p_curr->next) p_next = p_curr->next; p_curr->next = NULL;
    if(p_curr->pt) Patient_destroy(p_curr->pt); p_curr->pt = NULL;
    if(p_curr) free(p_curr); p_curr = NULL;
    p_curr = p_next;
  }
  if(p_curr->pt) Patient_destroy(p_curr->pt); p_curr->pt = NULL;
  if(p_curr) free(p_curr); p_curr = NULL;
}

PQ_node *PQ_list_node_extract(PQ_node *n)
{
  PQ_node *p_extracted, *p_left, *p_right;

  p_extracted = n;
  if(n->prev) p_left = n->prev;
  if(n->next) p_right = n->next;

  p_left->next = p_right;
  p_right->prev = p_left;

  if(p_extracted->next) p_extracted->next = NULL;
  if(p_extracted->prev) p_extracted->prev = NULL;

  return p_extracted;  
}

void PQ_node_destroy(PQ_node *n)
{
  if(n->pt) Patient_destroy(n->pt);
  if(n->pt) n->pt = NULL;
  if(n) free(n);
  n = NULL;
}
