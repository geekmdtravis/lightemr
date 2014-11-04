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
	 "6. Exit\n"
	 "\n"
	 "Please enter you selection: ", APP_VER);
}

void Display_patient_lookup_menu()
{
  system("clear");
  printf("\n[ Patient Look-up (%s) ]\n\n", APP_VER);
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

void Display_confirm_continue()
{
  printf("Press any key to continue");
  getchar(); // the first consumes the '\n'
  getchar(); // the second waits for user.
  system("clear");
}

int Display_confirm_exit()
{
  char selection;

  system("clear");
  printf("\n\nWARNING: You are about to exit %s.\n\n"
	 "Are you sure you'd like to exit (y/n)?  ", APP_VER);
  selection = getchar();
  selection = getchar();
  
  return ((selection == 'y' || selection == 'Y') ? 1 : 0);
}

void Evaluate_exit_signal(int exit)
{
  system("clear");
  if(!exit){
    printf("\nYou will head "
	   "back to main menu.\n\n");
  } else {
    printf("\n\n[ EXITING ]\n\n"
	   "Thank you for using %s.\n\n"
	   " - %s\n\n",
	   APP_VER, APP_AUTHOR);
  }
}

void Display_default_warning(char selection)
{
  system("clear");
  printf("\nWarning: '%c' is an invalid selection.\n"
             "Type a number as indicated  "
	 "and then press enter.\n\n", selection);
}
