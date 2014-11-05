#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "patient.h"

Patient *Patient_create()
{
  Patient *new_patient = malloc(sizeof(Patient));
  new_patient->name.first = malloc(sizeof(char) * MAX_NAME);
  new_patient->name.middle = malloc(sizeof(char) * MAX_NAME);
  new_patient->name.last = malloc(sizeof(char) * MAX_NAME);
  new_patient->addr.field1 = malloc(sizeof(char) * MAX_ADDR);
  new_patient->addr.field2 = malloc(sizeof(char) * MAX_ADDR);
  new_patient->addr.field3 = malloc(sizeof(char) * MAX_ADDR);
  new_patient->addr.field4 = malloc(sizeof(char) * MAX_ADDR);
  new_patient->contact.email = malloc(sizeof(char) * MAX_DATA);
  new_patient->emerg1.full_name = malloc(sizeof(char) * MAX_NAME * 2);
  new_patient->emerg1.relationship = malloc(sizeof(char) * MAX_DATA);
  new_patient->emerg1.contact.email = malloc(sizeof(char) * MAX_DATA);
  new_patient->emerg2.full_name = malloc(sizeof(char) * MAX_NAME * 2);
  new_patient->emerg2.relationship = malloc(sizeof(char) * MAX_DATA);
  new_patient->emerg2.contact.email = malloc(sizeof(char) * MAX_DATA);
  
  Patient_update_name(new_patient,
		      "First", "Middle", "Last");
  Patient_update_address(new_patient,
			 "Field 1", "Field 2", "Field 3", "Field 4");
  Patient_update_dob(new_patient, 0, 0, 0);
  Patient_update_contact(new_patient, 0, 0, 0, "No@Email.Given");
  Patient_update_emergency(&new_patient->emerg1,
			   "No contact given", 0, 0, 0, "None", "No@Email.Given");
  Patient_update_emergency(&new_patient->emerg2,
			   "No contact given", 0, 0, 0, "None", "No@Email.Given");
  new_patient->init = Patient_populate;
  
  return ((new_patient) ? new_patient : NULL);
}

BOOL Patient_destroy(Patient *p)
{
  if(p->name.first) free(p->name.first);
  if(p->name.middle) free(p->name.middle);
  if(p->name.last) free(p->name.last);
  if(p->addr.field1) free(p->addr.field1);
  if(p->addr.field2) free(p->addr.field2);
  if(p->addr.field3) free(p->addr.field3);
  if(p->addr.field4) free(p->addr.field4);
  if(p->contact.email) free(p->contact.email);
  if(p->emerg1.full_name) free(p->emerg1.full_name);
  if(p->emerg1.relationship) free(p->emerg1.relationship);
  if(p->emerg1.contact.email) free(p->emerg1.contact.email);
  if(p->emerg2.full_name) free(p->emerg2.full_name);
  if(p->emerg2.relationship) free(p->emerg2.relationship);
  if(p->emerg2.contact.email) free(p->emerg2.contact.email);

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
    strcpy(p->addr.field1, f1);
    strcpy(p->addr.field2, f2);
    strcpy(p->addr.field3, f3);
    strcpy(p->addr.field4, f4);

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

BOOL Patient_update_contact(Patient *p, int home, int work, int cell,  char *email)
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

BOOL Patient_update_emergency(Emergency_contact *ec, char *full_name, int home, int cell,
			      int work, char *relationship, char *email)
{
  if (ec) {
    strcpy(ec->contact.email, email);
    strcpy(ec->full_name, full_name);
    strcpy(ec->relationship, relationship);
    ec->contact.phone_h = home;
    ec->contact.phone_c = cell;
    ec->contact.phone_w = work;
    
    return TRUE;
  } else {
    return FALSE;
  }
}

Name Set_name(char *first, char *middle, char *last)
{
  Name new_n;

  strcpy(new_n.first, first);
  strcpy(new_n.middle, middle);
  strcpy(new_n.last, last);

  return new_n;
}

Birthdate Set_birthdate(int month, int day, int year)
{
  Birthdate new_b;

  new_b.month = month;
  new_b.day = day;
  new_b.year = year;

  return new_b;
}

Address Set_address(char *f1, char *f2, char *f3, char *f4)
{
  Address new_a;

  strcpy(new_a.field1, f1);
  strcpy(new_a.field2, f2);
  strcpy(new_a.field3, f3);
  strcpy(new_a.field4, f4);

  return new_a;
}

Contact Set_contact(long int phone_h, long int phone_c,
		    long int phone_w, char *email)
{
  Contact new_c;

  new_c.phone_h = phone_h;
  new_c.phone_c = phone_c;
  new_c.phone_w = phone_w;

  strcpy(new_c.email, email);

  return new_c;
}

Emergency_contact Set_emergency_contact(char *full_name, char *relationship,
					long int phone_h, long int phone_c,
					long int phone_w, char *email)
{
  Emergency_contact new_ec;

  strcpy(new_ec.full_name, full_name);
  strcpy(new_ec.relationship, relationship);
  new_ec.contact.phone_h = phone_h;
  new_ec.contact.phone_c = phone_c;
  new_ec.contact.phone_w = phone_w;
  strcpy(new_ec.contact.email, email);

  return new_ec;
}

void Patient_print_info(Patient *p)
{
    
  printf("Full name: %s %s %s\n"
	 " DOB: %lu/%lu/%lu\n"
	 " Address:\n"
	 "  %s\n"
	 "  %s\n"
	 "  %s\n"
	 "  %s\n"
	 " Email: %s\n"
	 " Home Phone: %lu\n"
	 " Cell Phone: %lu\n"
	 " Work Phone: %lu\n"
	 " Personal ID: %lu\n"
	 " MRN: %lu\n\n"
	 "Emergency Contact 1: %s\n"
	 " Relationship: %s\n"
	 " Phone: %lu\n"
	 " Cell: %lu\n"
	 " Work: %lu\n"
	 " Email: %s\n\n"
	 "Emergency Contact 2: %s\n"
	 " Relationship: %s\n"
	 " Phone: %lu\n"
	 " Cell: %lu\n"
	 " Work: %lu\n"
	 " Email: %s\n",
	 p->name.first,
	 p->name.middle,
	 p->name.last,
	 p->dob.month,
	 p->dob.day,
	 p->dob.year,
	 p->addr.field1,
	 p->addr.field2,
	 p->addr.field3,
	 p->addr.field4,
	 p->contact.email,
	 p->contact.phone_h,
	 p->contact.phone_c,
	 p->contact.phone_w,
	 p->pid,
	 p->mrn,
	 p->emerg1.full_name,
	 p->emerg1.relationship,
	 p->emerg1.contact.phone_h,
	 p->emerg1.contact.phone_c,
	 p->emerg1.contact.phone_w,
	 p->emerg2.contact.email,
	 p->emerg2.full_name,
	 p->emerg2.relationship,
	 p->emerg2.contact.phone_h,
	 p->emerg2.contact.phone_c,
	 p->emerg2.contact.phone_w,
	 p->emerg2.contact.email);
}
