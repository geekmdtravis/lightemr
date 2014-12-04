// file: note.c
#include "note.h"

char *Formatted_time(void)
{
  char *timeStr = malloc(sizeof(char) * MAX_DATE);
  time_t t;
  struct tm *tmp;
  const char *timeFormat = "%d/%m/%y %R\0";
  int rc;

  t = time(NULL);
  tmp = localtime(&t);

  if(!tmp) return "Failed to get time.\0";

  rc = strftime(timeStr, sizeof(timeStr), timeFormat, tmp);
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
  n->time = malloc(sizeof(char) * MAX_DATE);
  n->replaced = malloc(sizeof(char) * 4);
  n->text = malloc(sizeof(char) * MAX_NOTE);

  // Initialize note with basic values
  if(n->mrn) strcpy(n->mrn, mrn);
  // title excluded
  // author excluded
  if(n->time) strcpy(n->time, Formatted_time());
  if(n->replaced) strcpy(n->replaced, "no\0");
  // text excluded

  return n;
}

BOOL Note_destroy(Note *n)
{
  if(n->mrn) free(n->mrn); n->mrn = NULL;
  if(n->title) free(n->title); n->title = NULL;
  if(n->author) free(n->author); n->author = NULL;
  if(n->time) free(n->time); n->time = NULL;
  if(n->replaced) free(n->replaced); n->replaced = NULL;
  if(n->text) free(n->text); n->text = NULL;
  if(n) free(n); n = NULL;

  return (n == NULL) ? TRUE : FALSE;
}
// eof: note.c
