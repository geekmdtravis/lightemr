// file: patient_add.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "patient_add.h"
#include "dbg.h"

#define MAX_DATA 100

// remove last \n and replace it with \0
void trim(char *s);
// getline() and trim(); note this takes a
// string instead of a string pointer
ssize_t modgetl(char *s, size_t *n);
// getline() and atoi() the result
ssize_t modgetlatoi(int *i, size_t *n);

// Create patient, populate the fields.
Patient *Add_patient()
{
  Patient *p = Patient_create();
  size_t nbytes = MAX_DATA;
  ssize_t mr;

  // Get patients name
  printf("PATIENTS NAME\n"
	 "First: ");
  mr = modgetl(p->name.first, &nbytes);
  printf("Middle: ");
  mr = modgetl(p->name.middle, &nbytes);
  printf("Last: ");
  mr = modgetl(p->name.last, &nbytes);
  
  // Get patients date of birth
  printf("\nDATE OF BIRTH (Entered as decimal number)\n"
	 "Month: ");
  mr = modgetlatoi(&p->dob.month, &nbytes);
  printf("Day: ");
  mr = modgetlatoi(&p->dob.day, &nbytes);
  printf("Year: ");
  mr = modgetlatoi(&p->dob.year, &nbytes);
  printf("Personal ID (e.g. US Social Security): ");
  mr = modgetl(p->pid, &nbytes);
  
  // Get patients address
  printf("\nADDRESS\n");
  printf("1/4: ");
  mr = modgetl(p->addr.field1, &nbytes);
  printf("2/4: ");
  mr = modgetl(p->addr.field2, &nbytes);
  printf("3/4: ");
  mr = modgetl(p->addr.field3, &nbytes);
  printf("4/4: ");
  mr = modgetl(p->addr.field4, &nbytes);
  
  // Get patients contact information
  printf("\nCONTACT INFORMATION\n"
	 "Email address: ");
  mr = modgetl(p->contact.email, &nbytes);
  printf("Home phone: ");
  mr = modgetl(p->contact.phone_h, &nbytes);
  printf("Work phone: ");
  mr = modgetl(p->contact.phone_w, &nbytes);
  printf("Cell phone: ");
  mr = modgetl(p->contact.phone_c, &nbytes);
  
  // Get emergency contact information
  printf("\nWould you like to add an emergency contact (y/n)? ");
  char *selection = malloc(sizeof(char) * 2);
  mr = modgetl(selection, &nbytes);
  if (selection[0] == 'y' || selection[0] == 'Y') {
    printf("\nEMERGENCY CONTACT #1\n");
    printf("Name (full): ");
    mr = modgetl(p->emerg1.full_name, &nbytes);
    printf("Relationship: ");
    mr = modgetl(p->emerg1.relationship, &nbytes);
    printf("Email address: ");
    mr = modgetl(p->emerg1.contact.email, &nbytes);
    printf("Home phone: ");
    mr = modgetl(p->emerg1.contact.phone_h, &nbytes);
    printf("Work phone: ");
    mr = modgetl(p->emerg1.contact.phone_w, &nbytes);
    printf("Cell phone: ");
    mr = modgetl(p->emerg1.contact.phone_c, &nbytes);

    printf("\nWould you like to add an another emergency contact (y/n)? ");
    mr = modgetl(selection, &nbytes);
    if (selection[0] == 'y' || selection[0] == 'Y') {
      printf("\nEMERGENCY CONTACT #2\n");
      printf("Name (full): ");
      mr = modgetl(p->emerg2.full_name, &nbytes);
      printf("Relationship: ");
      mr = modgetl(p->emerg2.relationship, &nbytes);
      printf("Email address: ");
      mr = modgetl(p->emerg2.contact.email, &nbytes);
      printf("Home phone: ");
      mr = modgetl(p->emerg2.contact.phone_h, &nbytes);
      printf("Work phone: ");
      mr = modgetl(p->emerg2.contact.phone_w, &nbytes);
      printf("Cell phone: ");
      mr = modgetl(p->emerg2.contact.phone_c, &nbytes);
    }
  }

  check(mr > 0, "Failed to acquire input.");

  free(selection);
  
  return p;

 error:
  return NULL;
}

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
// eof: patient_add.c
