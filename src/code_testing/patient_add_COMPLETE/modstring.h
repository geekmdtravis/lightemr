// file: modstring.h

#ifndef _modstring_h
#define _modstring_h

#include "dbg.h"


#define MAX_DATA 100

// remove last \n and replace it with \0
void trim(char *s);
// getline() and trim(); note this takes a
// string instead of a string pointer
ssize_t modgetl(char *s, size_t *n);
// getline() and atoi() the result
ssize_t modgetlatoi(int *i, size_t *n);

#endif

// eof: modstring.h
