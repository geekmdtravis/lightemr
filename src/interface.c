#include "interface.h"

// Each line of text output to the interface, with a few exceptions
// where I'm limited by need to acquire user input, should be filtered
// through this function. This allows for uniformity in presentation.
void Print_interface_line(char *input, align_t align)
{
  int len = strlen(input);
  int i, j, offset;
  char line[MAX_LINE];

  for (i = 0; i < MAX_LINE; i++) {
    line[i] = ' ';
  }
  line[0] = '|';
  line[77] = '|';
  line[78] = '\n';
  line[79] = '\0';

  if (align == RIGHT) {
    offset = MAX_LINE_TEXT - len;
  } else if (align == CENTER) {
    offset = (MAX_LINE_TEXT - len) / 2;
  } else {
    offset = 1;
  }

  for (i = offset, j = 0; j < len && i < MAX_LINE_TEXT; j++, i++) {
    line[i] = input[j];
  }

  fprintf(stdout, "%s", line);
}

// This returns a string of a formtted current date
char *Formatted_date()
{
  time_t t = time(NULL);
  struct tm *tmp = localtime(&t);
  const char *timeFormat = "%A %B %d %Y\0";
  char *timeStr = malloc(sizeof(char) * MAX_DATE);
  int rc;

  if(!tmp) {
    return "Failed to get time.";
  } else {
    rc = strftime(timeStr, MAX_DATE, timeFormat, tmp);
    return ((rc == 0) ? "Unable to get time" : timeStr);
  }
}

/**********************************
         MAIN MENU
 *********************************/
void Display_main_menu()
{
  char *date = Formatted_date();  
  void (*prt)(char *input, align_t align) = Print_interface_line;
  
  system("clear");
  prt(THIN_LINE, LEFT);
  prt(date, CENTER);
  prt(THICK_LINE, LEFT);
  prt("Welcome to LightEMR", CENTER);
  prt(THIN_LINE, LEFT);
  prt(BLANK_LINE, LEFT);
  prt(" 1. Lookup Patient", CENTER);
  prt(" 2. Add Patient   ", CENTER);
  prt(" 3. Remove Patient", CENTER);
  prt(" 4. Help          ", CENTER);
  prt(" 5. Tools         ", CENTER);
  prt(" 6. Billing       ", CENTER);
  prt(" 7. Exit          ", CENTER);
  prt(BLANK_LINE, LEFT);
  prt(THIN_LINE, LEFT);
  fprintf(stdout, "%s", SELECTION_PROMPT_LONG);

  free(date);
}

/****************************************
          PATIENT LOOKUP
*****************************************/
void Display_patient_lookup_menu()
{
  char *date = Formatted_date();
  
  system("clear");
  void (*prt)(char *input, align_t align) = Print_interface_line;
  prt(THIN_LINE, LEFT);
  prt(date, CENTER);
  prt(THICK_LINE, LEFT);
  prt("LightEMR: Patient Look-up", CENTER);
  prt(THIN_LINE, LEFT);
  prt(BLANK_LINE, LEFT);
  prt(" 1. Find by MRN         ", CENTER);
  prt(" 2. Find by first name  ", CENTER);
  prt(" 3. Find by last name   ", CENTER);
  prt(" 4. Go back to main menu", CENTER);
  prt(BLANK_LINE, LEFT);
  prt(THIN_LINE, LEFT);
  printf("Please enter your selection: ");

  free(date);
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
	if (rc != 0) *pt = Patient_lookup(db, selection, "MRN");
	else printf("Error acquiring input.\n");
	break;
	
      case '2': // Lookup by first name
	printf("Please enter patients first name: ");
	rc = modgetl(selection, &nbytes);
	if (rc != 0) *pt = Patient_lookup(db, selection, "FIRST");
	else printf("Error acquiring input.\n");
	break;
	
      case '3': // Lookup by last name
	printf("Please enter patients last name: ");
	rc = modgetl(selection, &nbytes);
	if (rc != 0) *pt = Patient_lookup(db, selection, "LAST");
	else printf("Error acquiring input.\n");
	break;
	
    case '4': // Return to main menu
      if(pt) Patient_destroy(*pt);
      return 1;
      break;
      
    default:
      printf("Invalid entry.\n");
      break;
    }
    // Print patient info
    if(*pt != NULL) {
      do {
	fprintf(stdout, "\nMore detail on patient %s %s (Yes/No)? ",
	       (*pt)->name->first, (*pt)->name->last);
	rc = modgetl(selection, &nbytes);
	switch(selection[0]) {
	case 'Y':
	case 'y':
	  Patient_print_info(*pt);
	  break;
	case 'N':
	case 'n':
	  break;
	default:
	  printf("Invalid selection.\n");
	}
      } while (selection[0] != 'Y' &&
	     selection[0] != 'y' &&
	     selection[0] != 'N' &&
		 selection[0] != 'n');
      printf("\n");
    } else {
      printf("ERROR ");
      return -1;
    }

    return 0;
}

int Patient_add_commit(Patient *p)
{
  ssize_t rc;
  int selection;
  size_t nbytes = 2;
  void (*prt)(char *input, align_t align) = Print_interface_line;

  while(1) {
    system("clear");
    Patient_print_info(p);
    prt("PLEASE REVIEW THE ABOVE INFORMATION", CENTER);
    prt(THIN_LINE, LEFT);
    prt("Would you like to commit this patient to database?", LEFT);
    prt(" (1) Yes, commit this patient as above to database.", LEFT);
    prt(" (2) No, do not commit this patient information.", LEFT);
    prt(THIN_LINE, LEFT);
    fprintf(stdout, "%s", SELECTION_PROMPT_ABBREVIATED);
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
  char *date = Formatted_date();
  void (*prt)(char *input, align_t align) = Print_interface_line;
  
  system("clear");
  prt(THIN_LINE, LEFT);
  prt(date, CENTER);
  prt(THICK_LINE, LEFT);
  prt("LightEMR: Add Patient", CENTER);
  prt(THIN_LINE, LEFT);
  fprintf(stdout, "%s", "\n");

  free(date);
  
}

/******************************************
             PATIENT REMOVE
 *****************************************/

void Display_patient_remove_menu()
{
  void (*prt)(char *input, align_t align) = Print_interface_line;
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("LightEMR: Remove Patient", CENTER);
  prt(THICK_LINE, LEFT);
  prt(BLANK_LINE, LEFT);
  prt("Module in development.", CENTER);
  prt(BLANK_LINE, LEFT);
  prt(THIN_LINE, LEFT);
  
}

/******************************************
             HELP
 *****************************************/
void Display_help_menu()
{
  void (*prt)(char *input, align_t align) = Print_interface_line;
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("LightEMR: Help", CENTER);
  prt(THICK_LINE, LEFT);
  prt(BLANK_LINE, LEFT);
  prt("Module in development.", CENTER);
  prt(BLANK_LINE, LEFT);
  prt(THIN_LINE, LEFT);
}

/******************************************
             CLINICAL TOOLS
 *****************************************/

void Display_clinical_tools_menu()
{
  // ssize_t rc;
  size_t nbytes = 2;
  int selection;
  void (*prt)(char *input, align_t align) = Print_interface_line;
  
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("LightEMR: Tools", CENTER);
  prt(THICK_LINE, LEFT);
  prt(BLANK_LINE, LEFT);
  prt("1. Anion Gap", CENTER);
  prt(BLANK_LINE, LEFT);
  prt(THIN_LINE, LEFT);

  fprintf(stdout, "%s", SELECTION_PROMPT_LONG);
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
  void (*prt)(char *input, align_t align) = Print_interface_line;
  
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("LightEMR: Billing", CENTER);
  prt(THICK_LINE, LEFT);
  prt(BLANK_LINE, LEFT);
  prt("Module in development.", CENTER);
  prt(BLANK_LINE, LEFT);
  prt(THIN_LINE, LEFT);
}

/******************************************
             FLOW CONTROL
 *****************************************/

void Display_confirm_continue()
{
  char line[MAX_LINE_TEXT];
  char *cont= "[ Press RETURN to continue ]";
  int i, len, offset;
  len = strlen(cont);
  offset = (MAX_LINE_TEXT - len) / 2;

  for(i = 0; i < MAX_LINE_TEXT; i++){
    if (i < offset) {
      line[i] = ' ';
    } else if (i >= offset && i <= (offset + len)) {
      line[i] = cont[i - offset];
    }
    else {
      line[i] = '\0';
    }
  }
  line[MAX_LINE_TEXT] = '\0';
  
  fprintf(stdout, "%s", line);
  getchar();
}

// Prompts the user for confirmation of exit. If yes,
// return TRUE which can be passed to calling routine
// and in the case of our main program, allows for
// exit of program.
// RETURN: TRUE(1) if user wants to exit, FALSE(0) if not.
BOOL Display_confirm_exit()
{
  void (*prt)(char *input, align_t align) = Print_interface_line;
  size_t nbytes = 4;
  char *selection = malloc(sizeof(char) * 4);
  BOOL confirmExit = FALSE;

  system("clear");
  prt(THIN_LINE, LEFT);
  prt("LightEMR: Exit confirmation", CENTER);
  prt(THICK_LINE, LEFT);
  prt(BLANK_LINE, LEFT);
  prt("Are you sure you'd like to exit (y/n)?", CENTER);
  prt(BLANK_LINE, LEFT);
  prt(THIN_LINE, LEFT);

  do {
    fprintf(stdout, "  %s", SELECTION_PROMPT_LONG);
    modgetl(selection, &nbytes);
  
    switch(selection[0]) {
    case 'Y':
    case 'y':
      confirmExit = TRUE;
      break;

    case 'N':
    case 'n':
      confirmExit = FALSE;
      break;

    default:
      fprintf(stdout, "  %s", "  Incorrect selection\n");
      break;
    }
  } while (selection[0] != 'Y' && selection[0] != 'y' &&
	   selection[0] != 'N' && selection[0] != 'n');
  
  free(selection);
  
  return confirmExit;
}

// Look at the users decision to exit or not and
// show that the command was understood.
void Evaluate_exit_signal(BOOL exit)
{
  void (*prt)(char *input, align_t align) = Print_interface_line;
  system("clear");

  if(exit) {
    prt(THIN_LINE, LEFT);
    prt("LightEMR: Exiting the program", CENTER);
    prt(THICK_LINE, LEFT);
    prt(BLANK_LINE, LEFT);
    prt("This software is written and maintained by ", CENTER);
    prt("Travis Nesbit, MD. It is a free and open-  ", CENTER);
    prt("source software under the GNU GPL license. ", CENTER);
    prt(BLANK_LINE, LEFT);
    prt("Special thank you to:                      ", CENTER);
    prt(" - My wonderful wife                       ", CENTER);
    prt(" - The entire GNU/Linux community          ", CENTER);
    prt(BLANK_LINE, LEFT);
    prt(THIN_LINE, LEFT);
  } else {
    prt(THIN_LINE, LEFT);
    prt("LightEMR: You've chosen NOT to exit.", CENTER);
    prt(THICK_LINE, LEFT);
    prt(BLANK_LINE, LEFT);
    prt("You're being directed to the main menu.", CENTER);
    prt(BLANK_LINE, LEFT);
    prt(THIN_LINE, LEFT);
  }
}

void Display_default_warning(char selection)
{
  void (*prt)(char *input, align_t align) = Print_interface_line;
  char line[MAX_LINE_TEXT];
  int i;

  CLEAR_STRING(line, i, MAX_LINE_TEXT);
  sprintf(line, "WARNING: '%c' is an invalid selection.", selection);
  
  system("clear");
  prt(THIN_LINE, LEFT);
  prt(line, CENTER);
  prt(THICK_LINE, LEFT);
  prt(BLANK_LINE, CENTER);
  prt("Please type a number as indicated and press ENTER.", CENTER);
  prt(BLANK_LINE, CENTER);
  prt(THIN_LINE, CENTER);
}
