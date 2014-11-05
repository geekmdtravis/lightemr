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
  long int phone_h;
  long int phone_c;
  long int phone_w;
  char *email;
} Contact;

typedef struct Emergency_contact {
  char *full_name; 
  char *relationship;
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
  BOOL (*init)(struct Patient *self, Name *name, Birthdate *dob, Address *addr,
		      Contact *contact, Emergency_contact *emerg1,
		      Emergency_contact *emerg2,
		      int pid, int mrn);
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
BOOL Patient_update_emergency(Emergency_contact *ec, char *full_name,
			      int home, int cell, int work, char *email);
Name Set_name(char *first, char *middle, char *last);
Birthdate Set_birthdate(int month, int day, int year);
Address Set_address(char *f1, char *f2, char *f3, char *f4);
Contact Set_contact(long int phone_h, long int phone_c,
		    long int phone_w, char *email);
Emergency_contact Set_emergency_contact(char *full_name, char *relationship,
					long int phone_h, long int phone_c,
					long int phone_w, char *email);
void Patient_print_info(Patient *p);

#endif

// eof: patient.h
