#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "patient.h"

Patient *Patient_create()
{
  Patient *new_patient = malloc(sizeof(Patient));

  Patient_update_name(new_patient, "First", "Middle", "Last");
  Patient_update_address(new_patient, "Field 1", "Field 2", "Field 3", "Field 4");
  Patient_update_dob(new_patient, 0, 0, 0);
  Patient_update_contact(new_patient, 0, 0, 0, "No@Email.Given");

  // set the emergency contact 1
  
  strcpy(new_patient->emerg1.full_name, "No contact given");
  strcpy(new_patient->emerg1.relationship, "No relationship given");
  new_patient->emerg1.contact.phone_h = 0;
  new_patient->emerg1.contact.phone_c = 0;
  new_patient->emerg1.contact.phone_w = 0;  
  strcpy(new_patient->emerg1.contact.email, "No@Emerg1Email.Given");
  // set the emergency contact 2
  strcpy(new_patient->emerg2.full_name, "No contact given");
  strcpy(new_patient->emerg2.relationship, "No relationship given");  
  new_patient->emerg2.contact.phone_h = 0;
  new_patient->emerg2.contact.phone_c = 0;
  new_patient->emerg2.contact.phone_w = 0;
  strcpy(new_patient->emerg2.contact.email, "No@Emerg2Email.Given");
  
  return ((new_patient) ? new_patient : NULL);
}

BOOL Patient_destroy(Patient *p)
{
  // if you can destroy the patient
  // return 1 for true. this allows
  // if (patient_destroy) statements.
  if(p) {
    free(p);
    return TRUE; // return 1
  } else {
    return FALSE; // return 0
  }
}

BOOL Patient_populate(Patient *self, Name *name, Birthdate *dob, Address *addr,
		      Contact *contact, Emergency_contact *emerg1,
		      Emergency_contact *emerg2,
		      int pid, int mrn)
{
  if (self) {
    if (name) self->name = *name;
    if (dob) self->dob = *dob;
    if (addr) self->addr = *addr;
    if (contact) self->contact = *contact;
    if (emerg1) self->emerg1 = *emerg1;
    if (emerg2) self->emerg2 = *emerg2;
    if (pid) self->pid = pid;
    if (mrn) self->mrn = mrn;
    
    return TRUE;
  } else {
    return FALSE;
  }

}
BOOL Patient_update_name(Patient *p, char *first, char *middle, char *last)
{
  if(p) {
    strcpy(p->name.first, first);
    strcpy(p->name.middle, middle);
    strcpy(p->name.last, last);

    return TRUE;
  } else {
    return FALSE;
  }
}

BOOL Patient_update_address(Patient *p,
			    char *f1, char *f2, char *f3, char *f4)
{
  if(p) {
    strcpy(p->addr.field1, "Field 1");
    strcpy(p->addr.field2, "Field 2");
    strcpy(p->addr.field3, "Field 3");
    strcpy(p->addr.field4, "Field 4");

    return TRUE;
  } else {
    return FALSE;
  }
}

BOOL Patient_update_dob(Patient *p, int month, int day, int year)
{
  if (p) {
    p->dob.month = month;
    p->dob.day = day;
    p->dob.year = year;

    return TRUE;
  } else {
    return FALSE;
  }
}

BOOL Patient_update_contact(Patient *p, int home, int work, int cell, char *email)
{
  if (p) {
    p->contact.phone_h = home;
    p->contact.phone_w = work;
    p->contact.phone_c = cell;
    strcpy(p->contact.email, email);

    return TRUE;
  } else {
    return FALSE;
  }
}

void Patient_update_emergency(Patient *p)
{}
