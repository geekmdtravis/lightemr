// file: patient_add.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "patient_add.h"

#define MAX_DATA 100

void trim(char *s);
ssize_t modgetl(char *s, size_t *n);
ssize_t modgetlatoi(long unsigned int *i, size_t *n);

int Add_patient()
{
  Patient *p = Patient_create();
  size_t nbytes = MAX_DATA;
  ssize_t mr;
  
  printf("PATIENTS NAME\n");
  printf("First: ");
  mr = modgetl(p->name.first, &nbytes);
  printf("Middle: ");
  mr = modgetl(p->name.middle, &nbytes);
  printf("Last: ");
  mr = modgetl(p->name.last, &nbytes);
  
  printf("\nDATE OF BIRTH (Entered as decimal number)\n");
  printf("Month: ");
  mr = modgetlatoi(&p->dob.month, &nbytes);
  printf("Day: ");
  mr = modgetlatoi(&p->dob.day, &nbytes);
  printf("Year: ");
  mr = modgetlatoi(&p->dob.year, &nbytes);
  printf("Personal ID (e.g. US Social Security): ");
  mr = modgetlatoi(&p->pid, &nbytes);

  printf("\nADDRESS\n");
  printf("Field 1 (of 4): ");
  mr = modgetl(p->addr.field1, &nbytes);
  printf("Field 2 (of 4): ");
  mr = modgetl(p->addr.field2, &nbytes);
  printf("Field 3 (of 4): ");
  mr = modgetl(p->addr.field3, &nbytes);
  printf("Field 4 (of 4): ");
  mr = modgetl(p->addr.field4, &nbytes);

  printf("\nCONTACT INFORMATION\n");
  printf("Email address: ");
  mr = modgetl(p->contact.email, &nbytes);
  printf("Home phone: ");
  mr = modgetlatoi(&p->contact.phone_h, &nbytes);
  printf("Work phone: ");
  mr = modgetlatoi(&p->contact.phone_w, &nbytes);
  printf("Cell phone: ");
  mr = modgetlatoi(&p->contact.phone_c, &nbytes);

  printf("\nWould you like to add an emergency contact? (y/n)");
  char *selection = malloc(sizeof(char) * 2);
  mr = modgetl(selection, &nbytes);
  if (selection[0] == 'y' || selection[0] == 'Y') {
    printf("\nEMERGENCY CONTACT #1\n");
    printf("Name (full): ");
    mr = modgetl(p->emerg1.full_name, &nbytes);
    printf("Relationship: ");
    mr = modgetl(p->emerg1.relationship, &nbytes);    
  }

  printf("\nWould you like to add an another emergency contact? (y/n)");
  if (selection[0] == 'y' || selection[0] == 'Y') {
    printf("\nEMERGENCY CONTACT #2\n");
    printf("Name (full): ");
    mr = modgetl(p->emerg2.full_name, &nbytes);
    printf("Relationship: ");
    mr = modgetl(p->emerg2.relationship, &nbytes);    
  }
  free(selection);
  

  if (mr && mr != EOF) {
    system("clear");
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

ssize_t modgetlatoi(long unsigned int *i, size_t *n)
{
	ssize_t mr;
	char *tempstr = malloc(sizeof(char) * MAX_DATA);
	
    mr = getline(&tempstr, n, stdin);
    *i = atoi(tempstr);

    free(tempstr);
	
	return mr;
}

void trim(char *s)
{
	if(s){
		s[strlen(s) - 1] = '\0';
	}
}
// eof: patient_add.c
