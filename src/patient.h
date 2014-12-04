// file: patient.h

#ifndef _patient_h
#define _patient_h

#include "defs.h"

typedef struct Name {
  char *first;
  char *middle;
  char *last;
} Name;

typedef struct Address {
  char *field1;
  char *field2;
  char *field3;
  char *field4;
} Address;

typedef struct Birthdate {
  int month;
  int day;
  int year;
} Birthdate;

typedef struct Contact {
  char *phone_h;
  char *phone_c;
  char *phone_w;
  char *email;
} Contact;

typedef struct Emergency_contact {
  char *full_name; 
  char *relationship;
  Contact *contact;
} Emergency_contact;
  

typedef struct Patient {
  Name *name;
  Birthdate *dob;
  Address *addr;
  Contact *contact;
  Emergency_contact *emerg1;
  Emergency_contact *emerg2;
  char *pid;
  char *mrn;
  BOOL (*init)(struct Patient *self, Name *name,
	       Birthdate *dob, Address *addr,
	      Contact *contact, Emergency_contact *emerg1,
	      Emergency_contact *emerg2,
	      char *pid, char *mrn);
} Patient;

Patient *Patient_create(void);
BOOL Patient_destroy(Patient *p);

BOOL Patient_populate(Patient *self, Name *name,
		      Birthdate *dob, Address *addr,
		      Contact *contact,
		      Emergency_contact *emerg1,
		      Emergency_contact *emerg2,
		      char *pid, char *mrn);
BOOL Patient_update_name(Patient *p, char *first,
		      char *middle, char *last);
BOOL Patient_update_address(Patient *p, char *f1,
		      char *f2, char *f3, char *f4);
BOOL Patient_update_dob(Patient *p, int month,
		      int day, int year);
BOOL Patient_update_contact(Patient *p, char *home,
		      char *cell, char *work, char *email);
BOOL Patient_update_emergency(Emergency_contact *ec,
		      char *full_name, char *home,
		      char *cell, char *work,
		      char *relationship, char *email);
Name *Set_name(char *first, char *middle, char *last);
Birthdate *Set_birthdate(int month, int day, int year);
Address *Set_address(char *f1, char *f2,
		      char *f3, char *f4);
Contact *Set_contact(char *phone_h, char *phone_c,
		      char *phone_w, char *email);
Emergency_contact *Set_emergency_contact(char *full_name,
		      char *relationship,
		      char *phone_h, char *phone_c,
		      char *phone_w, char *email);
void Patient_print_info(Patient *p);
void Patient_print_search_result(Patient *p);
#endif

// eof: patient.h
