// file: note.c

#include "note.h"

char *Formatted_time(void)
{
  char *timeStr = malloc(sizeof(char) * MAX_DATE);
  time_t t;
  struct tm *tmp;
  const char *timeFormat = "%d/%m/%y %T\0";
  int rc;

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
  n->author = malloc(sizeof(char) * MAX_NAME * 2);
  n->time = Formatted_time();
  n->time_sec = time(NULL);
  n->replaced = malloc(sizeof(char) * 4);
  n->text = malloc(sizeof(char) * MAX_NOTE);

  // Initialize note with basic values
  if(n->mrn) strcpy(n->mrn, mrn);
  // title excluded temporarily
  // author excluded temporarily
  // Formatted time already done above as passed pointer
  if(n->replaced) strcpy(n->replaced, "no\0");
  // text excluded temporarily

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
// eof: note.c
