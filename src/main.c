// file: main.cp
// TODO: Work on case '1', looking up a patient from a database.

#include <string.h>
#include "interface.h"
#include "patient.h" 
#include "patient_add.h"
#include "database.h"
#include "modstring.h"

int main()
{
  /* return values for use with getline() */
  ssize_t rc = 0; // return value
  size_t nbytes = 2; // for two chars max ('n' + '\x')
  char *selection = malloc(sizeof(char) * MAX_DATA);
  
  /* tracking the exit status of the program */
  BOOL EXIT = FALSE;

  /* For use with Sqlite3 */
  sqlite3 *db; 
  char *query;
  char *sqlError;

  /* A single program alone will be in workspace. */
  Patient *pt = NULL;

  /* Establish a database connection. If there is no
     database file present, one will be created. Then
     validate. Establish a patient demographics table
     unless one is already present.

     Likely, this will be moved into it's own function
     and multiple tables will be created at this point.
  */
  rc = sqlite3_open("lightemr.data", &db); // 40 byte memleak here?
  check(rc == SQLITE_OK, "Could not open database.")
  rc = Patient_demographics_table_create(db);
  //  check(rc == SQLITE_OK, "Couldn't create demographics table.");

  // MAIN PROGRAM LOOP
  do {
    Display_main_menu();
    rc = getline(&selection, &nbytes, stdin);
    check(rc != 0, "Error acquiring input.\n"
	  "Was your input a numeric digit?\n"
	  "The program will now exit.\n");

    switch(selection[0]) { // Select only first character.
    case '1':
      Display_patient_lookup_menu();
      if(pt) Patient_destroy(pt);
      rc = getline(&selection, &nbytes, stdin);
      check(rc != 0, "Input error.");
      Process_patient_lookup(selection, pt, db);
      break;

    case '2':
      Display_patient_add_menu();
      if(pt) Patient_destroy(pt);
      pt = Add_patient();
      query = Create_add_user_query(pt);
      rc = sqlite3_exec(db, query, NULL, 0, &sqlError);
      break;
      
    case '3':
      // Presently only removing active
      // patient. Needs to remove from data-
      // base. No database implmented yet.
      Display_patient_remove_menu();
      if(pt) {
	Patient_destroy(pt);
	printf("Patient has been removed.\n\n");
	pt = NULL;
      } else {
	printf("No active patients.\n\n");
      }
      break;
      
    case '4':
      // empty
      Display_help_menu();
      break;
      
    case '5':
      // empty
      Display_clinical_tools_menu();
      break;
      
    case '6':
      // empty
      Display_billing_menu();
      break;

    case 'q':
    case 'Q':
    case '7':
      // Waits for exit status to be
      // TRUE then cleans up the heap
      // and exits. 
      EXIT = Display_confirm_exit();
      Evaluate_exit_signal(EXIT);
      if(EXIT){
	if(selection) {
	  free(selection);
	  selection = NULL;
	}
	if(pt) Patient_destroy(pt);
	// if(sqlError) sqlite3_free(sqlError);
      	sqlError = NULL;
	sqlite3_close(db);
	db = NULL;
	exit(EXIT_SUCCESS);
      }
      break;
      
    default:
      Display_default_warning(selection[0]);
      break;
    }
    
    Display_confirm_continue();
    
  } while (!EXIT);
  
 error:
  exit(EXIT_FAILURE);
}
