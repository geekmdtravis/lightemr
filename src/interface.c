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
  int selectionNum = 0;
  
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
    if(*pt) {
      do {
	fprintf(stdout, "\nMore detail on patient %s %s (Yes/No)? ",
	       (*pt)->name->first, (*pt)->name->last);
	rc = modgetl(selection, &nbytes);
	switch(selection[0]) {
	case 'Y':
	case 'y':
	  Patient_print_info(*pt);
	  Display_confirm_continue();
	  fprintf(stdout, "\n");
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
      // Enter the patient portal
      if (rc != 0) {
	while(selectionNum != 3){
	  Display_patient_portal_menu(*pt);
	  rc = modgetlatoi(&selectionNum, &nbytes);
	  switch(selectionNum) {
	  case 1:
	    fprintf(stdout, "Option 1 not implemented yet.\n\n");
	    Display_confirm_continue();
	    break;
	  case 2:
	    fprintf(stdout, "Option 2 not implemented yet.\n\n");
	    Display_confirm_continue();
	    break;
	  case 3:
	    break;
	  default:
	    fprintf(stdout, "Selection '%d' is not valid.\n\n", selectionNum);
	    Display_confirm_continue();
	    break;
	  }
	  fprintf(stdout, "\n");
	}
      }
    } else {
      fprintf(stdout, "ERROR: ");
      return -1;
    }

    return 0;
}


/******************************************
            PATIENT_PORTAL
 *****************************************/
void Display_patient_portal_menu(Patient *pt)
{
  void (*prt)(char *input, align_t align) = Print_interface_line;
  char *line = malloc(sizeof(char) * MAX_LINE_TEXT);
    
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("Clinical Portal", CENTER);
  sprintf(line, "[ %s, %s %s ] [ MRN: %s ] [ DOB: %d/%d/%d ]",
	  pt->name->last, pt->name->first, pt->name->middle,
	  pt->mrn, pt->dob->day, pt->dob->month, pt->dob->year);
  prt(line, CENTER);
  prt(THICK_LINE, LEFT);
  prt("1. Add note         ", CENTER);
  prt("2. Search notes     ", CENTER);
  prt("3. Back to main menu", CENTER);
  prt(THIN_LINE, LEFT);
  fprintf(stdout, "%s", SELECTION_PROMPT_LONG);

  if(line) free(line); line = NULL;
}

/******************************************
             PATIENT ADD
 *****************************************/

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

// Process the clinicians request to calc anion gap withint program
// RETURN: 0 for good output, -1 for unexpected or poor output
int Process_anion_gap()
{
  BMP b; // basic metabolic panel
  int rc, i;
  int gap;
  double rd;
  double normalAlb;
  double alb;
  size_t nbytes = 4;
  char *userInput = malloc(sizeof(char) * nbytes);
  void (*prt)(char *input, align_t align) = Print_interface_line;
  char line[MAX_LINE_TEXT];
  
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("LightEMR: Anion Gap Calculator", CENTER);
  prt(THICK_LINE, LEFT);
  fprintf(stdout, "%s", "  Sodium  : ");
  modgetlatoi(&b.na, &nbytes);
  fprintf(stdout, "%s", "  Chloride: ");
  modgetlatoi(&b.cl, &nbytes);
  fprintf(stdout, "%s", "  Bicarb  : ");
  modgetlatoi(&b.bicarb, &nbytes);

  rc = Calculate_anion_gap(b.na, b.cl, b.bicarb);
  prt(THIN_LINE, LEFT);
  CLEAR_STRING(line, i, MAX_LINE_TEXT);
  sprintf(line, "Anion gap: %d", rc);
  prt(line, CENTER);
  CLEAR_STRING(line, i, MAX_LINE_TEXT);
  sprintf(line, "(%d - (%d + %d))", b.na, b.cl, b.bicarb);
  prt(line, CENTER);
  prt(THIN_LINE, LEFT);
  
  if(rc != -99) {
    printf("  Would you like to calculate for hypoalbuminemia (y/n)? ");
    modgetl(userInput, &nbytes);
    switch(userInput[0]) {
    case 'Y':
    case 'y':
      gap = rc;
      printf("  Normal albumin (4.2): ");
      modgetlatof(&normalAlb, &nbytes);
      printf("  Observed albumin    : ");
      modgetlatof(&alb, &nbytes);
      rd = Calculate_corrected_anion_gap(gap, normalAlb, alb);
      prt(THIN_LINE, LEFT);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "Corrected anion gap: %.2f", rd);
      prt(line, CENTER);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "(%.2f x (%.2f - %.2f))", 2.5, normalAlb, alb);
      prt(line, CENTER);
      prt(THIN_LINE, LEFT);
      break;
      
    case 'N':
    case 'n':
      prt(THIN_LINE, LEFT);
      prt("Correction will not be calculated.  ", CENTER);
      prt(THIN_LINE, LEFT);
      break;

    default:
      prt(THIN_LINE, LEFT);
      prt("  Incorrect selection. You will be returned to the main menu.", LEFT);
      prt(THIN_LINE, LEFT);
      return -1;
      break;
    }
    free(userInput);
    return 0;
  } else {
    prt(THIN_LINE, LEFT);
    CLEAR_STRING(line, i, MAX_LINE_TEXT);
    sprintf(line, "  Result of %d indicating input error.\n\n", rc);
    prt(line, LEFT);
    prt(THIN_LINE, LEFT);
    free(userInput);
    return -1;
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

/*****************************************************
                      DATABASE INTERFACE
 *****************************************************/

// REturns selection # in addition to setting selection
// flag to true
int Lookup_result_selection(PQ_node *head, char *identifier)
{
  void (*prt)(char *input, align_t align) = Print_interface_line;
  PQ_node *curr;
  int selection, i;
  size_t nbytes = 4;
  char ptResult[MAX_LINE_TEXT];
  BOOL found = FALSE;

  system("clear");
  prt(THIN_LINE, LEFT);
  prt("LightEMR: Lookup Patient", CENTER);
  prt(THICK_LINE, LEFT);
  prt("Multiple results returned. Select desired patient.", CENTER);
  prt(THIN_LINE, LEFT);

  //  for(curr = head; curr->next; curr = (curr->next) ? curr->next : tail) {
  for(curr = head; curr->next; curr = curr->next) {
   CLEAR_STRING(ptResult, i, MAX_LINE_TEXT);
   sprintf(ptResult, "[ # %d] %s, %s %c. MRN: %s DOB %d/%d/%d  ",
	   curr->count,
	   curr->pt->name->last,
	   curr->pt->name->first,
	   curr->pt->name->middle[0],
	   curr->pt->mrn,
	   curr->pt->dob->month,
	   curr->pt->dob->day,
	   curr->pt->dob->year);
   prt(ptResult, LEFT);
  }
  CLEAR_STRING(ptResult, i, MAX_LINE_TEXT);
  sprintf(ptResult, "[ # %d] %s, %s %c. MRN: %s DOB %d/%d/%d  ",
	  curr->count,
	  curr->pt->name->last,
	  curr->pt->name->first,
	  curr->pt->name->middle[0],
	  curr->pt->mrn,
	  curr->pt->dob->month,
	  curr->pt->dob->day,
	  curr->pt->dob->year);
  prt(ptResult, LEFT);
  prt(BLANK_LINE, LEFT);
  prt(THIN_LINE, LEFT);

  fprintf(stdout, "%s", SELECTION_PROMPT_LONG);
  modgetlatoi(&selection, &nbytes);

  for(curr = head; curr->next; curr = curr->next) {
    if (curr->count == selection) {
      curr->selected = TRUE;
      selection = curr->count;
      found = TRUE;
    }
  }
  if (curr->count == selection) {
    curr->selected = TRUE;
    selection = curr->count;
    found = TRUE;
  }

  if (found == FALSE) {
    fprintf(stdout, "No patient was found with the \"identifier\" %s.\n", identifier);
  }

  return selection;
}
