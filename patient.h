// file: patient.h

#ifndef _patient_h
#define _patient_h

#define MAX_NAME 40
#define MAX_ADDR 50

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

typedef struct Patient {
  Name name;
  Birthdate dob;
  Address addr;
  Contact contact;
  int pid;
  int mrn;
} Patient;
  

#endif

// eof: patienet.h
