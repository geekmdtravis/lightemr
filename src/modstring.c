// file: modstring.c

#include <stdlib.h>
#include <string.h>
#include "modstring.h"

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

void trim(char *s)
{
	if(s){
		s[strlen(s) - 1] = '\0';
	}
}

// eof: modstring.c
