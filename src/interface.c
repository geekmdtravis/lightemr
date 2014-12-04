#include "interface.h"

void Display_main_menu()
{
  system("clear");
  Display_menu_time();
  printf("\n"
         "[ Welcome to %s ]\n"
         "\n"
         "             -= MENU =-             \n"
	 "\n"
         "1. Patient Lookup\n"
	 "2. Add Patient\n"
	 "3. Remove Patient\n"
	 "4. Help\n"
	 "5. Clinical Tools\n"
	 "6. Billing\n"
	 "7. Exit\n"
	 "\n"
	 "Please enter your selection: ", APP_VER);
}

void Display_menu_time()
{
  char *timeStr = malloc(sizeof(char) * MAX_DATE);
  //char timeStr[MAX_DATE];
  time_t t;
  struct tm *tmp;
  const char *timeFormat = "%A %B %d %Y\0";
  int rc;

  t = time(NULL);
  tmp = localtime(&t);

  if(!tmp) printf("Failed to get time.");

  rc = strftime(timeStr, MAX_DATE, timeFormat, tmp);
  if(rc == 0) printf("Failed to create formatted time string.");

  printf("%s\n", timeStr);

  free(timeStr);
}

/****************************************
          PATIENT LOOKUP
*****************************************/
void Display_patient_lookup_menu()
{
  system("clear");
  printf("\n[ Patient Look-up (%s) ]\n\n", APP_VER);
  printf("\t1. Lookup by MRN\n");
  printf("\t2. Lookup by first name\n");
  printf("\t3. Lookup by last name\n");
  printf("\n");
  printf("Please enter your selection: ");

}

int Process_patient_lookup(char *selection, Patient **pt, sqlite3 *db)
{
  size_t nbytes = MAX_DATA; // for two chars max ('n' + '\x')
  ssize_t rc = 0;
  
    // Lookup patient
    switch(selection[0]) {
      case '1': // Lookup by MRN
	printf("Please enter patients MRN: ");
	rc = modgetl(selection, &nbytes);
	if (rc != 0) *pt = Patient_lookup_mrn(selection, db);
	else printf("Error acquiring input.\n");
	break;
	
      case '2': // Lookup by first name
	printf("Please enter patients first name: ");
	rc = modgetl(selection, &nbytes);
	if (rc != 0) *pt = Patient_lookup_first(selection, db);
	else printf("Error acquiring input.\n");
	break;
	
      case '3': // Lookup by last name
	printf("Please enter patients last name: ");
	rc = modgetl(selection, &nbytes);
	if (rc != 0) *pt = Patient_lookup_last(selection, db);
	else printf("Error acquiring input.\n");
	break;
	
      default:
	printf("Invalid entry.\n");
	break;
    }

    printf("\n");
    // Print patient info
    if(*pt != NULL) {
      Patient_print_search_result(*pt);
      
      while (selection[0] != 'Y' &&
	     selection[0] != 'y' &&
	     selection[0] != 'N' &&
	     selection[0] != 'n') {
	printf("\nMore detail on patient %s %s (Yes/No)? ",
	       (*pt)->name->first, (*pt)->name->last);
	rc = modgetl(selection, &nbytes);
	switch(selection[0]) {
	case 'Y':
	case 'y':
	  system("clear");
	  Patient_print_info(*pt);
	  break;
	case 'N':
	case 'n':
	  break;
	default:
	  printf("Invalid selection.\n");
	}
      }
      printf("\n");
    } else {
      printf("Patient not found.\n\n");
      return -1;
    }

    return 0;
}

int Patient_add_commit(Patient *p)
{
  ssize_t rc;
  int selection;
  size_t nbytes = 2;

  while(1) {
    system("clear");
    printf("\n"
	   "ATTENTION: Please review the information below.\n"
	   "\n");
    Patient_print_info(p);
    printf( "\n"
	    "Would you like to commit this information to the database?\n"
	    "(1) YES\n"
	    "(2) NO\n"
	    "::> ");
    rc = modgetlatoi(&selection, &nbytes);
    if (rc == 0) {
      printf("\nError acquiring input\n");
      return 0;

    }
    switch(selection) {
    case 1:
      printf("\nCommitting to database now.\n");
      return 1;
      break;
    case 2:
      printf("\nThis information will not be commit to database.\n");
      return 0;
      break;
    default:
      printf("\nInvalid entry. Please try again.\n\n");
      break;
    }
  }
}

/******************************************
             PATIENT ADD
 *****************************************/

void Display_patient_add_menu()
{
  system("clear");
  printf("\n[ Patient Add Menu (%s) ]\n\n", APP_VER);
}

/******************************************
             PATIENT REMOVE
 *****************************************/

void Display_patient_remove_menu()
{
  system("clear");
  printf("\n[ Patient Remove Menu (%s) ]\n\n", APP_VER);
}

/******************************************
             HELP
 *****************************************/
void Display_help_menu()
{
  system("clear");
  printf("\n[ Help (%s) ]\n\n", APP_VER);
}

/******************************************
             CLINICAL TOOLS
 *****************************************/

void Display_clinical_tools_menu()
{
  // ssize_t rc;
  size_t nbytes = 2;
  int selection;
  
  system("clear");
  printf("\n[ Clinical Tools (%s) ]\n\n", APP_VER);
  printf("\n 1. Anion Gap.\n\n");

  printf("Please enter your selection: ");
  modgetlatoi(&selection, &nbytes);
  switch(selection){
  case 1:
    Process_anion_gap();
    break;
  default:
    printf("That was not an option.");
    break;
  }
}

/******************************************
             BILLING
 *****************************************/
void Display_billing_menu()
{
  system("clear");
  printf("\n[ Billing (%s) ]\n\n", APP_VER);
}

/******************************************
             FLOW CONTROL
 *****************************************/

void Display_confirm_continue()
{
  printf("Press RETURN to continue");
  getchar();
  system("clear");
}

// Prompts the user for confirmation of exit. If yes,
// return TRUE which can be passed to calling routine
// and in the case of our main program, allows for
// exit of program.
// RETURN: TRUE(1) if user wants to exit, FALSE(0) if not.
BOOL Display_confirm_exit()
{
  char selection;

  system("clear");
  printf("\n\nWARNING: You are about to exit %s.\n\n"
	 "Are you sure you'd like to exit (y/n)?  ", APP_VER);
  selection = getchar();
  
  return ((selection == 'y' || selection == 'Y') ? TRUE : FALSE);
}

// Look at the users decision to exit or not and
// show that the command was understood.
void Evaluate_exit_signal(BOOL exit)
{
  system("clear");

  if(exit) {
    printf("\n\n[ EXITING ]\n\n"
	   "Thank you for using %s.\n\n"
	   " - %s\n\n",
	   APP_VER, APP_AUTHOR);
  } else {
    printf("\nYou will head "
	   "back to main menu.\n\n");
  }
}

void Display_default_warning(char selection)
{
  system("clear");
  printf("\nWarning: '%c' is an invalid selection.\n"
             "Type a number as indicated  "
	 "and then press enter.\n\n", selection);
}
