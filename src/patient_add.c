// file: patient_add.c

#include <stdio.h>
#include <stdlib.h>
#include "patient.h"
#include "patient_add.h"

#define MAX_DATA 100

int Add_patient()
{
  int rc;
  Patient *p = Patient_create();
  
  printf("First name: ");
  fscanf(stdin, "%s", p->name.first);
  getchar();
  printf("Middle name: ");
  fscanf(stdin, "%s", p->name.middle);
  getchar();
  printf("Last name: ");
  fscanf(stdin, "%s", p->name.last);
  getchar();
  /*  printf("Month of birth: ");
  fscanf(stdin, "%d", p->dob.month);
  printf("Day of birth: ");
  fscanf(stdin, "%d", p->dob.day);
  printf("Year of birth: ");
  fscanf(stdin, "%d", p->dob.year);*/
  printf("Address field (1/4): ");
  fscanf(stdin, "%s", p->addr.field1);
  getchar();
  printf("Address field (2/4): ");
  fscanf(stdin, "%s", p->addr.field2);
  getchar();
  printf("Address field (3/4): ");
  fscanf(stdin, "%s", p->addr.field3);
  getchar();
  printf("Address field (4/4): ");
  fscanf(stdin, "%s", p->addr.field4);
  getchar();

  Patient_print_info(p);

  Patient_destroy(p);
  
  return 0;
}

// eof: patient_add.c
