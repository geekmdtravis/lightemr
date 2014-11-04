// file: patient.h

#ifndef _patient_h
#define _patient_h

#define MAX_NAME 40
#define MAX_ADDR 50
#define MAX_DATA 100

typedef int BOOL;
#define FALSE 0;
#define TRUE  1;

typedef struct Name {
  char first[MAX_NAME];
  char middle[MAX_NAME];
  char last[MAX_NAME];
} Name;

typedef struct Address {
  char field1[MAX_ADDR];
  char field2[MAX_ADDR];
  char field3[MAX_ADDR];
  char field4[MAX_ADDR];
} Address;

typedef struct Birthdate {
  int month;
  int day;
  int year;
} Birthdate;

typedef struct Contact {
  long int phone_h;
  long int phone_c;
  long int phone_w;
  char email[MAX_ADDR];
} Contact;

typedef struct Emergency_contact {
  char full_name[MAX_NAME + MAX_NAME]; //first + last
  char relationship[MAX_DATA];
  Contact contact;
} Emergency_contact;
  

typedef struct Patient {
  Name name;
  Birthdate dob;
  Address addr;
  Contact contact;
  Emergency_contact emerg1;
  Emergency_contact emerg2;
  int pid;
  int mrn;
} Patient;
  

Patient *Patient_create(void);
BOOL Patient_destroy(Patient *p);

BOOL Patient_populate(Patient *self, Name *name, Birthdate *dob, Address *addr,
		      Contact *contact, Emergency_contact *emerg1,
		      Emergency_contact *emerg2,
		      int pid, int mrn);
BOOL Patient_update_name(Patient *p, char *first, char *middle, char *last);
BOOL Patient_update_address(Patient *p, char *f1, char *f2, char *f3, char *f4);
BOOL Patient_update_dob(Patient *p, int month, int day, int year);
BOOL Patient_update_contact(Patient *p, int home, int cell, int work, char *email);
void Patient_update_emergency(Patient *p);

#endif

/*  USAGE EXAMPLE
    
  Patient p1;
  strcpy(p1.name.first, "Joe");
  strcpy(p1.name.middle, "B");
  strcpy(p1.name.last, "Schmoe");
  p1.dob.month = 4;
  p1.dob.day = 21;
  p1.dob.year = 1942;
  strcpy(p1.addr.field1, "1 Street");
  strcpy(p1.addr.field2, "Romona, CA");
  strcpy(p1.addr.field3, "92688");
  strcpy(p1.addr.field4, "United States of America");
  strcpy(p1.contact.email, "joebschmoe@gmail.com");
  p1.contact.phone_h = 5555555555;
  p1.contact.phone_c = 5556665555;
  p1.contact.phone_w = 5557775555;
  p1.pid = 333221234;
  p1.mrn = 1234567890;
  strcpy(p1.emerg1.full_name, "Jan Schmoe");
  strcpy(p1.emerg1.relationship, "Wife");
  p1.emerg1.contact.phone_h = 5555555559;
  p1.emerg1.contact.phone_c = 5556665550;
  p1.emerg1.contact.phone_w = 5557775551;
  strcpy(p1.emerg1.contact.email, "janaschmoe@yahoo.com");

*/

// eof: patienet.h
