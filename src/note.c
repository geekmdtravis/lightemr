// file: note.c

#include "note.h"

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

Note *Note_add(Patient *p)
{
  Note *n = NULL;
  size_t nbytes = MAX_DATA; // changes this when at text segment to MAX_NOTE
  ssize_t mr = 0;
  char *selection = malloc(sizeof(char) * 6); // quit\n\0 = 6

  // get mrn
  n = Note_create(p->mrn);
  // If there is no patient, return and avoid segfault
  if(!n) return NULL;

  enum Note_type { NEW_HPI = 1, FOLLOW_UP = 2, EVENT = 3} note_type;
  note_type = 0;

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
  
  // get time (char)
  // Auto-completing on creation
  
  // get time_sec (time_t)
  // Auto-completing on creation
  
  // get replaced (char)
  // Not yet implemented

  // Setup for note entry
  void (*prt)(char *input, align_t align) = Print_interface_line;
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("PATIENT NOTE ENTRY", CENTER);
  prt(THICK_LINE, LEFT);
  prt("[ 8000 character maximum. ]", CENTER);
  prt(THIN_LINE, LEFT);
  fprintf(stdout, "\n\n "
	  SELECTION_PROMPT_MINIMAL);
  // reallocate to selection
  if(selection) free(selection); selection = NULL;
  selection = malloc(sizeof(char) * MAX_NOTE);
  
  // get text; nbytes = MAX_NOTE
  nbytes = MAX_NOTE;
  mr = modgetl(selection, &nbytes);
  strncpy(n->text, selection, MAX_NOTE);

  // Clean up before exit
  if(selection) free(selection); selection = NULL;
  
  // reset nbytes
  nbytes = MAX_DATA;

  return n;
}

// eof: note.c
