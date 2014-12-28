// file: note.c

#include "note.h"


/**********************************************
 * Formatted_time()
 **********************************************
 * This function returns a date and time string
 * literal. The Note n->time object is where
 * this is primarily intended to be used. However
 * it might have uses in different places.
 * TODO: consider moving this to a different
 * file.
 *********************************************/
char *Formatted_time(void)
{
  char *timeStr = malloc(sizeof(char) * MAX_DATE);
  time_t t;
  struct tm *tmp;
  const char *timeFormat = "%d/%m/%y %T\0";
  int rc = 0;

  t = time(NULL);
  tmp = localtime(&t);

  if(!tmp) return "Failed to get time.\0";

  rc = strftime(timeStr, MAX_DATE, timeFormat, tmp);
  if(rc == 0) return "Failed create formatted time string.\0";

  return timeStr;
}


/****************************************
 *Note_create(char *mrn)
 ****************************************
 * Initialize a note object and return it.
 * All field objects are defined.
 ***************************************/
Note *Note_create(char *mrn)
{
  // Allocate heap space for note struct
  Note *n = malloc(sizeof(Note));

  // Allocate heap space for members of note struct
  n->mrn = malloc(sizeof(char) * MAX_ID);
  n->title = malloc(sizeof(char) * MAX_DATA);
  n->author = malloc(sizeof(char) * MAX_DATA);
  n->time = Formatted_time();
  n->time_sec = time(NULL);
  n->replaced = malloc(sizeof(char) * 4);
  n->text = malloc(sizeof(char) * MAX_NOTE);

  // Initialize note with basic values
  if(n->mrn) strcpy(n->mrn, mrn);
  if(n->title) strcpy(n->title, "Note Title");
  if(n->author) strcpy(n->author, "Author");
  // Formatted time already done above as passed pointer
  if(n->replaced) strcpy(n->replaced, "no\0");
  if(n->text) strcpy(n->text, "Text goes here.");

  return n;
}

/****************************************
 * Note_copy()
 ****************************************
 * Returns a note object. This is primarily
 * utilized when a note is found in the
 * database and we need to extract a single
 * note from the liked list of Note_query
 * nodes. Was having difficulty plucking
 * it from the linked list and destroying
 * the object so created the copy function
 * for both the patient and the note
 * to circumvent that problem.
 ***************************************/
Note *Note_copy(Note *n)
{
  Note *p_copy = Note_create("NULL");

  strcpy(p_copy->mrn, n->mrn);
  strcpy(p_copy->title, n->title);
  strcpy(p_copy->author, n->author);
  strcpy(p_copy->time, n->time);
  p_copy->time_sec = n->time_sec;
  strcpy(p_copy->replaced, n->replaced);
  strcpy(p_copy->text, n->text);

  return p_copy;
}

/***************************************
 * Note_add(Patient *p)
 **************************************
 * Create a new note and initialize the
 * values to the patient where appropriate.
 * Note type and text content of the note
 * will be input by user.
 * Return value is a note object.
 **************************************/
Note *Note_add(Patient *p)
{
  Note *n = NULL;
  size_t nbytes = MAX_DATA; // changes this when at text segment to MAX_NOTE
  ssize_t mr = 0;
  char *selection = malloc(sizeof(char) * 6); // quit\n\0 = 6
  selection[0] = '\0';

  // get mrn
  n = Note_create(p->mrn);
  // If there is no patient, return and avoid segfault
  if(!n) return NULL;

  // Enumate the three different note types
  enum Note_type { NEW_HPI = 1, FOLLOW_UP = 2, EVENT = 3} note_type;
  note_type = 0;

  // while the user has not made a valid decision
  // ask user to select appropriate note type from
  // the three options below.
  while (note_type != NEW_HPI &&
	 note_type != FOLLOW_UP &&
	 note_type != EVENT &&
	 selection[0] != 'q' &&
	 selection[0] != 'Q' &&
	 selection[0] != '4'){
    system("clear");
    // get title
    Display_note_type();
    mr = modgetl(selection, &nbytes);

    // Initialize the note title
    switch(selection[0]) {
    case '1':
      note_type = NEW_HPI;
      strncpy(n->title, "New Patient H&P", MAX_DATA);
      break;
    case '2':
      note_type = FOLLOW_UP;
      strncpy(n->title, "Follow-up Note", MAX_DATA);
      break;
    case '3':
      note_type = EVENT;
      strncpy(n->title, "Event Note", MAX_DATA);
      break;
    case 'q':
    case 'Q':
    case '4':
      break;
    default:
      fprintf(stdout, "Incorrect selection.\n");
      break;
    }
  }
  
  // get author
  strncpy(n->author, "Unspecified User", MAX_DATA);
  
  // get time (char): Auto-completing on creation
  // get time_sec (time_t): Auto-completing on creation
  // get replaced (char): Not yet implemented; defaults to 'no'

  // Setup for note entry; ask user to write note
  // #TODO: This needs to have a text editor function;
  // presently there is no ability to create newlines, tabs,
  // delete, etc. 
  void (*prt)(char *input, align_t align) = Print_interface_line;
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("PATIENT NOTE ENTRY", CENTER);
  prt(THICK_LINE, LEFT);
  prt("[ 8000 character maximum. ]", CENTER);
  prt(THIN_LINE, LEFT);
  fprintf(stdout, "\n\n "
	  SELECTION_PROMPT_MINIMAL);
  // reallocate to selection such that it's appropriately
  // sized for the note
  if(selection) free(selection); selection = NULL;
  selection = malloc(sizeof(char) * MAX_NOTE);
  nbytes = MAX_NOTE;
  // Get the text entry for the note.
  mr = modgetl(selection, &nbytes);
  strncpy(n->text, selection, MAX_NOTE);

  // Clean up before exit
  if(selection) free(selection); selection = NULL;
  
  // reset nbytes
  nbytes = MAX_DATA;

  return n;
}

/*********************************************
 * Note_destroy(Note *n)
 *********************************************
 * Clean up the heap where the note was
 * previously located.
 * Returns true on success;
 ********************************************/
BOOL Note_destroy(Note *n)
{
  if(n->mrn) free(n->mrn); n->mrn = NULL;
  if(n->title) free(n->title); n->title = NULL;
  if(n->author) free(n->author); n->author = NULL;
  if(n->time) free(n->time); n->time = NULL;
  if(n->replaced) free(n->replaced); n->replaced = NULL;
  if(n->text) free(n->text); n-> text = NULL;
  if(n) free(n); n = NULL;

  return (n == NULL) ? TRUE : FALSE;
}


// eof: note.c
