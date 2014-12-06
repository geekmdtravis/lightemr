// file: modstring.c

// TO DO: Modify modgetlatoi() so that it
// no longer requires the user to provide n.

#include "modstring.h"

// This function is a wrapper for the getline
// function that includes the small modification
// that the last character, which is often \n
// is transformed to a \0 via the trim() function
// I am no sure why, but 'n' and the allocated size of
// 's' must be the same. Getline's realloc call leads
// to an invalid free and memory leak.
// Example usage: modgetl(s, 10) for an s of
// malloc(sizeof(char) * 10);
// When not possible to do this, use getline() and then
// trim() as it handles these things appropriately.
// Of note, I intentionally made this to pass the
// buffer length with the address operator. I may revise this
// but I thought it would be useful for the user to recognize
// that we're passing the address. 
// RETURN: same as getline()
ssize_t modgetl(char *s, size_t *n)
{
  ssize_t mr; // same return type as getline

  if(s) {
    mr = getline(&s, n, stdin);
    trim(s);
    check(mr > 0, "Failed to acquire input.");
    return mr;
  } else {
    goto error;
  }
  
 error:
  return -1;
}
// Identical to above, except atoi is invoked to
// convert a temporary string into an integer.
// This will be changed so that the user will not
// be required to pass the n value.
// RETURN: same as getline()
ssize_t modgetlatoi(int *i, size_t *n)
{
  ssize_t mr;
  *n = MAX_DATA;
  char *tempstr = malloc(sizeof(char) * MAX_DATA);

  if(i) {
    mr = getline(&tempstr, n, stdin);
    trim(tempstr);
    *i = atoi(tempstr);
    check(mr > 0, "Failed to acquire input.");
    free(tempstr);
    return mr;
  } else {
    goto error;
  }
  
 error:
  return -1;
}

// like above but with atof
ssize_t modgetlatof(double *d, size_t *n)
{
  int mr;
  *n = MAX_DATA;
  char *tempstr = malloc(sizeof(char) * MAX_DATA);

  if(d) {
    mr = getline(&tempstr, n, stdin);
    trim(tempstr);
    *d = atof(tempstr);
    check(mr > 0, "Failed to acquire input.");
    free(tempstr);
    return mr;
  } else {
    goto error;
  }
  
 error:
  return -1;
}

// makes the last character in a string a
// null terminator. This is useful in that
// we can replace bothersome escape characters
// such as \n which cause unwanted behavior when
// displayed. 
void trim(char *s)
{

  if(s){
    s[strlen(s) - 1] = '\0';
  }
}

char *Convert_to_upper(char *str)
{
  int i;
  char *upperStr = malloc(sizeof(char) * strlen(str) + 1);
  
  for (i = 0; i < strlen(str) && str[i] != '\0'; i++) {
    upperStr[i] = toupper(str[i]);
  }
  upperStr[i] = '\0';

  return upperStr;
}

// eof: modstring.c
