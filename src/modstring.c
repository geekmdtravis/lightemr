// file: modstring.c

#include <stdlib.h>
#include <string.h>
#include "modstring.h"

// This function is a wrapper for the getline
// function that includes the small modification
// that the last character, which is often \n
// is transformed to a \0 via the trim() function
// RETURN: same as getline()
ssize_t modgetl(char *s, size_t *n)
{
	ssize_t mr;
	
    mr = getline(&s, n, stdin);
    trim(s);
    
    check(mr > 0, "Failed to acquire input.");
    
    return mr;

 error:
    return -1;
}

// Like above, except that it passes a pointer from
// the integer in the lower stack frame to the
// function as an argument and returns a trimmed and
// atoi'd value. Effectively, "3\n" -> 3
// RETURN: same as getline()
ssize_t modgetlatoi(int *i, size_t *n)
{
	ssize_t mr;
	char *tempstr = malloc(sizeof(char) * MAX_DATA);
	
    mr = getline(&tempstr, n, stdin);
    trim(tempstr);
    *i = atoi(tempstr);
    
    free(tempstr);

    check(mr > 0, "Failed to acquire input.");
	
    return mr;

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

// eof: modstring.c
