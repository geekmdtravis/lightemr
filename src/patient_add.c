// file: patient_add.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "patient_add.h"

#define MAX_DATA 100

void trim(char *s);
ssize_t modgetl(char *s, size_t *n);

int Add_patient()
{
  Patient *p = Patient_create();
  size_t nbytes = MAX_DATA;
  ssize_t mr;
  
  printf("Patients name:\n");
  printf("First: ");
  mr = modgetl(p->name.first, &nbytes);
  printf("Middle: ");
  mr = modgetl(p->name.middle, &nbytes);
  printf("Last: ");
  mr = modgetl(p->name.last, &nbytes);
  
  if (mr && mr != EOF) {
	Patient_print_info(p);
  }
  
  Patient_destroy(p);
  
  return 0;
}

ssize_t modgetl(char *s, size_t *n)
{
	ssize_t mr;
	
    mr = getline(&s, n, stdin);
    trim(s);
	
	return mr;
}

void trim(char *s)
{
	if(s){
		s[strlen(s) - 1] = '\0';
	}
}
// eof: patient_add.c
