// file: modstring.h

#ifndef _modstring_h
#define _modstring_h

#include "defs.h"
#include "dbg.h"

// remove last \n and replace it with \0
void trim(char *s);
// getline() and trim(); note this takes a
// string instead of a string pointer
ssize_t modgetl(char *s, size_t *n);
// getline() and atoi() the result
ssize_t modgetlatoi(int *i, size_t *n);
// getline() and atof() the result
ssize_t modgetlatof(double *d, size_t *n);
char *Convert_to_upper(char *str);

#endif

// eof: modstring.h
