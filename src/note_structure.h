// file: note_structure.h

#ifndef _note_structure_h
#define _note_structure_h

typedef struct Note {
  char *mrn;
  char *title;
  char *author;
  char *time;
  time_t time_sec;
  char *replaced;
  char *text;
} Note;

#endif

// eof: note_structure.h
