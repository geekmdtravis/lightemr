// file: note.c
#include "note.h"

Note *Note_create()
{
  // Create new note
  Note *n = malloc(sizeof(Note));

  n->mrn = malloc(sizeof(char) * MAX_ID);
  n->title = malloc(sizeof(char) * MAX_DATA);
  n->author = malloc(sizeof(char) * MAX_NAME * 2);
  n->time = malloc(sizeof(time_t));
  n->replaced = malloc(sizeof(char) * 4);
  n->text = malloc(sizeof(char) * MAX_NOTE);

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
