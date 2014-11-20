#include "interface.h"

void Display_main_menu()
{
  system("clear");
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

int Process_patient_lookup(char *selection, Patient *pt, sqlite3 *db)
{
  size_t nbytes = 2; // for two chars max ('n' + '\x')
  ssize_t rc = 0;
  
    // Lookup patient
    switch(selection[0]) {
      case '1': // Lookup by MRN
	printf("Please enter patients MRN: ");
	rc = getline(&selection, &nbytes, stdin);
	check(rc != 0, "Input error.");
	trim(selection); // remove escape chars
	pt = Patient_lookup_mrn(selection, db);
	if(pt) {
	  printf("Found patient %s, %s.\n", pt->name->last, pt->name->first);
	}
	break;
	
      case '2': // Lookup by first name
	printf("Please enter patients first name: ");
	rc = getline(&selection, &nbytes, stdin);
	check(rc != 0, "Input error.");
	trim(selection); // remove escape chars
	pt = Patient_lookup_first(selection, db);
	if(pt) {
	  printf("Found patient %s, %s.\n", pt->name->last, pt->name->first);
	}
	break;
	
      case '3': // Lookup by last name
	printf("Please enter patients last name: ");
	rc = getline(&selection, &nbytes, stdin);
	check(rc != 0, "Input error.");
	trim(selection); // remove escape chars
	pt = Patient_lookup_last(selection, db);
	if(pt) {
	  printf("Found patient %s, %s.\n", pt->name->last, pt->name->first);
	}
	break;
	
      default:
	printf("Invalid entry.\n");
	break;
      }
      
      // Prompt to display patient info
      if(pt != NULL) {
	printf("Would you like to display patient info (y/n)? ");
	rc = getline(&selection, &nbytes, stdin);
	check(rc != 0, "Input error.");
	trim(selection); // remove escape chars
      }
      if(pt != NULL && selection[0] == 'y') {
	Patient_print_info(pt);
      } else if (pt != NULL && selection[0] == 'n') {
	printf("Information for patient %s, %s will not be displayed.\n",
		 pt->name->last, pt->name->first);
      } else {
	printf("No patient selected.\n");
      }

      return 0;

 error:
      exit(EXIT_FAILURE);

}


void Display_patient_add_menu()
{
  system("clear");
  printf("\n[ Patient Add Menu (%s) ]\n\n", APP_VER);
}


void Display_patient_remove_menu()
{
  system("clear");
  printf("\n[ Patient Remove Menu (%s) ]\n\n", APP_VER);
}


void Display_help_menu()
{
  system("clear");
  printf("\n[ Help (%s) ]\n\n", APP_VER);
}

void Display_clinical_tools_menu()
{
  system("clear");
  printf("\n[ Clinical Tools (%s) ]\n\n", APP_VER);
  printf("\n 1. Anion Gap.\n\n");
}

void Display_billing_menu()
{
  system("clear");
  printf("\n[ Billing (%s) ]\n\n", APP_VER);
}

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
