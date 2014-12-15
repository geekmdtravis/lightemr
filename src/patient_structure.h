// file patient_structure.h

#ifndef _patient_structure_h
#define _patient_structure_h

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
} Patient;

#endif

// eof: patient_structure.h
