#include "patient.h"

// Create and return a patient object
Patient *Patient_create()
{
  Patient *new_patient = malloc(sizeof(Patient));

  // Gain heap space for pid and mrn
  new_patient->pid = malloc(sizeof(char) * MAX_ID);
  strcpy(new_patient->pid, "\0");
  new_patient->mrn = malloc(sizeof(char) * MAX_ID);
  strcpy(new_patient->mrn, "\0");
  // Gain heap space for dob
  new_patient->dob = malloc(sizeof(Birthdate));
  // Gain heap space for name
  new_patient->name = malloc(sizeof(Name));
  new_patient->name->first = malloc(sizeof(char) * MAX_NAME);
  new_patient->name->middle = malloc(sizeof(char) * MAX_NAME);
  new_patient->name->last = malloc(sizeof(char) * MAX_NAME);
  // Gain heap space for address
  new_patient->addr = malloc(sizeof(Address));
  new_patient->addr->field1 = malloc(sizeof(char) * MAX_ADDR);
  new_patient->addr->field2 = malloc(sizeof(char) * MAX_ADDR);
  new_patient->addr->field3 = malloc(sizeof(char) * MAX_ADDR);
  new_patient->addr->field4 = malloc(sizeof(char) * MAX_ADDR);
  // Gain heap space for contact info
  new_patient->contact = malloc(sizeof(Contact));
  new_patient->contact->email = malloc(sizeof(char) * MAX_DATA);
  new_patient->contact->phone_c = malloc(sizeof(char) * MAX_PHONE);
  new_patient->contact->phone_h = malloc(sizeof(char) * MAX_PHONE);
  new_patient->contact->phone_w = malloc(sizeof(char) * MAX_PHONE);
  // Gain heap space for emergency contact
  new_patient->emerg1 = malloc(sizeof(Emergency_contact));
  new_patient->emerg1->full_name = malloc(sizeof(char) * MAX_NAME * 2);
  new_patient->emerg1->relationship = malloc(sizeof(char) * MAX_DATA);
  new_patient->emerg1->contact = malloc(sizeof(Contact));
  new_patient->emerg1->contact->email = malloc(sizeof(char) * MAX_ADDR);
  new_patient->emerg1->contact->phone_h = malloc(sizeof(char) * MAX_PHONE);
  new_patient->emerg1->contact->phone_c = malloc(sizeof(char) * MAX_PHONE);
  new_patient->emerg1->contact->phone_w = malloc(sizeof(char) * MAX_PHONE);
  // Gain heap space for emergency contact
  new_patient->emerg2 = malloc(sizeof(Emergency_contact));
  new_patient->emerg2->full_name = malloc(sizeof(char) * MAX_NAME * 2);
  new_patient->emerg2->relationship = malloc(sizeof(char) * MAX_DATA);
  new_patient->emerg2->contact = malloc(sizeof(Contact));
  new_patient->emerg2->contact->email = malloc(sizeof(char) * MAX_DATA);
  new_patient->emerg2->contact->phone_h = malloc(sizeof(char) * MAX_PHONE);
  new_patient->emerg2->contact->phone_c = malloc(sizeof(char) * MAX_PHONE);
  new_patient->emerg2->contact->phone_w = malloc(sizeof(char) * MAX_PHONE);

  // Give place-holder values to name, address, contact
  // and emergency contact fields
  Patient_update_name(new_patient,"First", "Middle", "Last");
  Patient_update_address(new_patient,"Field 1", "Field 2", "Field 3", "Field 4");
  Patient_update_dob(new_patient, 0, 0, 0);
  Patient_update_contact(new_patient, "5555555555", "5555555555", "5555555555",
			 "No@Email.Given");
  Patient_update_emergency(new_patient->emerg1,
		      "No contact given", "5555555555", "5555555555",
			   "5555555555", "None", "No@Email.Given");
  Patient_update_emergency(new_patient->emerg2,
		      "No contact given", "5555555555", "5555555555",
			   "5555555555", "None", "No@Email.Given");

  return ((new_patient) ? new_patient : NULL);
}

// Look to see if each field that shoud have heap
// spaces does, and then free it.
// RETURN VALUE: TRUE(1) for success, FALSE(0) for failure
BOOL Patient_destroy(Patient *p)
{
  if(!p) return FALSE;

  // free memory for pid, mrn, dob
  if(p->pid) free(p->pid); p->pid = NULL;
  if(p->mrn) free(p->mrn); p->mrn = NULL;
  if(p->dob) free(p->dob); p->dob = NULL;

  // free memory for each name and name pointer
  if(p->name->first) free(p->name->first); p->name->first = NULL;
  if(p->name->middle) free(p->name->middle); p->name->middle = NULL;
  if(p->name->last) free(p->name->last); p->name->last = NULL;
  if(p->name) free(p->name); p->name = NULL;

  // free memory for each field of address and address pointer
  if(p->addr->field1) free(p->addr->field1); p->addr->field1 = NULL;
  if(p->addr->field2) free(p->addr->field2); p->addr->field2 = NULL;
  if(p->addr->field3) free(p->addr->field3); p->addr->field3 = NULL;
  if(p->addr->field4) free(p->addr->field4); p->addr->field4 = NULL;
  if(p->addr) free(p->addr); p->addr = NULL;

  // free memory for each field of contact and contact pointer
  if(p->contact->email) free(p->contact->email); p->contact->email = NULL;
  if(p->contact->phone_c) free(p->contact->phone_c); p->contact->phone_c = NULL;
  if(p->contact->phone_h) free(p->contact->phone_h); p->contact->phone_h = NULL;
  if(p->contact->phone_w) free(p->contact->phone_w); p->contact->phone_w = NULL;
  if(p->contact) free(p->contact); p->contact = NULL;

  // free memory for each field of emergency contact and the ec pointer
  if(p->emerg1->full_name) free(p->emerg1->full_name); p->emerg1->full_name = NULL;
  if(p->emerg1->relationship) free(p->emerg1->relationship); p->emerg1->relationship = NULL;
  if(p->emerg1->contact->email) {
    free(p->emerg1->contact->email);
    p->emerg1->contact->email = NULL;
  }
  if(p->emerg1->contact->phone_h) {
    free(p->emerg1->contact->phone_h);
    p->emerg1->contact->phone_h = NULL;
  }
  if(p->emerg1->contact->phone_c) {
    free(p->emerg1->contact->phone_c);
    p->emerg1->contact->phone_c = NULL;
  }
  if(p->emerg1->contact->phone_w) {
    free(p->emerg1->contact->phone_w);
    p->emerg1->contact->phone_w = NULL;
  }
  if(p->emerg1->contact) free(p->emerg1->contact); p->emerg1->contact = NULL;
  if(p->emerg1) free(p->emerg1); p->emerg1 = NULL;

  // same as above
  if(p->emerg2->full_name) free(p->emerg2->full_name); p->emerg2->full_name = NULL;
  if(p->emerg2->relationship) free(p->emerg2->relationship); p->emerg2->relationship = NULL;
  if(p->emerg2->contact->email) {
    free(p->emerg2->contact->email);
    p->emerg2->contact->email = NULL;
  }
  if(p->emerg2->contact->phone_h) {
    free(p->emerg2->contact->phone_h);
    p->emerg2->contact->phone_h = NULL;
  }
  if(p->emerg2->contact->phone_c) {
    free(p->emerg2->contact->phone_c);
    p->emerg2->contact->phone_c = NULL;
  }
  if(p->emerg2->contact->phone_w) {
    free(p->emerg2->contact->phone_w);
    p->emerg2->contact->phone_w = NULL;
  }
  if(p->emerg2->contact) free(p->emerg2->contact); p->emerg2->contact = NULL;
  if(p->emerg2) free(p->emerg2); p->emerg2 = NULL;
  
  // free the patient object from memory
  free(p);
  p = NULL;
  
  return TRUE;
}

// Take a pointer to a patient object and then copy strings
// to the name fields. 
// TO DO: There needs to be a way to update individual name fields.
// RETURN: TRUE(1) for success, and FALSE(0) for failure
BOOL Patient_update_name(Patient *p, char *first, char *middle, char *last)
{
  if(p) {
    strcpy(p->name->first, first);
    strcpy(p->name->middle, middle);
    strcpy(p->name->last, last);

    return TRUE;
  } else {
    return FALSE;
  }
}

// Take a pointer to a patient object and then copy strings
// to the address fields. 
// RETURN: TRUE(1) for success, and FALSE(0) for failure
BOOL Patient_update_address(Patient *p,
			    char *f1, char *f2, char *f3, char *f4)
{
  if(p) {
    strcpy(p->addr->field1, f1);
    strcpy(p->addr->field2, f2);
    strcpy(p->addr->field3, f3);
    strcpy(p->addr->field4, f4);

    return TRUE;
  } else {
    return FALSE;
  }
}

// Take a pointer to a patient object and update the date of
// birth fields.
// TO DO: There needs to be a way to update individual fields.
// RETURN: TRUE(1) for success, and FALSE(0) for failure
BOOL Patient_update_dob(Patient *p, int month, int day, int year)
{
  if (p) {
    p->dob->month = month;
    p->dob->day = day;
    p->dob->year = year;

    return TRUE;
  } else {
    return FALSE;
  }
}

// Take a pointer to a patient object and update the contact
// information fields.
// TO DO: There needs to be a way to update individual fields.
// RETURN: TRUE(1) for success and FALSE(0) for failure
BOOL Patient_update_contact(Patient *p, char *home, char *work, char *cell,  char *email)
{
  if (p) {
    strcpy(p->contact->phone_h, home);
    strcpy(p->contact->phone_w, work);
    strcpy(p->contact->phone_c, cell);
    strcpy(p->contact->email, email);

    return TRUE;
  } else {
    return FALSE;
  }
}

// Take a pointer to a patient objet and update the 
// emergency contact information.
// TO DO: There needs to be a way to update individual fields.
// RETURN: TRUE(1) for success and FALSE(0) for failure
BOOL Patient_update_emergency(Emergency_contact *ec, char *full_name, char *home, char *cell,
			      char *work, char *relationship, char *email)
{
  if (ec) {
    strcpy(ec->contact->email, email);
    strcpy(ec->full_name, full_name);
    strcpy(ec->relationship, relationship);
    strcpy(ec->contact->phone_h, home);
    strcpy(ec->contact->phone_c, cell);
    strcpy(ec->contact->phone_w, work);
    
    return TRUE;
  } else {
    return FALSE;
  }
}

// Likely only to be used for internal tests. INitialize
// a local Name object with values;
Name *Set_name(char *first, char *middle, char *last)
{
  Name *new_n = malloc(sizeof(Name));

  strcpy(new_n->first, first);
  strcpy(new_n->middle, middle);
  strcpy(new_n->last, last);

  return new_n;
}

// Likely only to be used for internal tests. Initialize
// a local Birthdate object with values.
Birthdate *Set_birthdate(int month, int day, int year)
{
  Birthdate *new_b = malloc(sizeof(Birthdate));

  new_b->month = month;
  new_b->day = day;
  new_b->year = year;

  return new_b;
}

// Likely to be used for internal tests. Initialize a
// local Address object with values.
Address *Set_address(char *f1, char *f2, char *f3, char *f4)
{
  Address *new_a = malloc(sizeof(Address));

  strcpy(new_a->field1, f1);
  strcpy(new_a->field2, f2);
  strcpy(new_a->field3, f3);
  strcpy(new_a->field4, f4);

  return new_a;
}

// LIkely to be used for internal tests. Initialize a
// local Contact object with values.
Contact *Set_contact(char *phone_h, char *phone_c,
		    char *phone_w, char *email)
{
  Contact *new_c = malloc(sizeof(Contact));

  strcpy(new_c->phone_h, phone_h);
  strcpy(new_c->phone_c, phone_c);
  strcpy(new_c->phone_w, phone_w);
  strcpy(new_c->email, email);

  return new_c;
}

// LIkely to be used for internal tests. Initialize a 
// local Emergency_contact object with values.
Emergency_contact *Set_emergency_contact(char *full_name, char *relationship,
					char *phone_h, char *phone_c,
					char *phone_w, char *email)
{
  Emergency_contact *new_ec = malloc(sizeof(Emergency_contact));

  strcpy(new_ec->full_name, full_name);
  strcpy(new_ec->relationship, relationship);
  strcpy(new_ec->contact->phone_h, phone_h);
  strcpy(new_ec->contact->phone_c, phone_c);
  strcpy(new_ec->contact->phone_w, phone_w);
  strcpy(new_ec->contact->email, email);

  return new_ec;
}


// This is most likely useful only in tests, however this allows
// a patient object to be populated by passing pointers to
// structure objects and reassingning the patient objects pointers
// Because it's accepting these structures and there isn't anywhere
// that users are working with the granularized forms of these 
// structures, it's likely that this would be receiving pointers to
// variables located in stack space. So, this is likely to only be 
// used in tests.
// RETURN: TRUE(1) for success, FALSE(0) for failure
BOOL Patient_populate(Patient *self, Name *name, Birthdate *dob,
		      Address *addr, Contact *contact,
		      Emergency_contact *emerg1,
		      Emergency_contact *emerg2,
		      char *pid, char *mrn)
{
  if (self) {
    if (name) self->name = name;
    if (dob) self->dob = dob;
    if (addr) self->addr = addr;
    if (contact) self->contact = contact;
    if (emerg1) self->emerg1 = emerg1;
    if (emerg2) self->emerg2 = emerg2;
    if (pid) self->pid = pid;
    if (mrn) self->mrn = mrn;
    
    return TRUE;
  } else {
    return FALSE;
  }

}

// A rudimentary patient information display function. It is 
// ugly but exhaustive in that it shows all available fields in 
// a patient object.
void Patient_print_info(Patient *p)
{
  void (*prt)(char *input, align_t align) = Print_interface_line;
  char *upperFirst = Convert_to_upper(p->name->first);
  char *upperMiddle = Convert_to_upper(p->name->middle);
  char *upperLast = Convert_to_upper(p->name->last);
  char line[MAX_LINE_TEXT];
  int i;

  if(p) {
    system("clear");
    CLEAR_STRING(line, i, MAX_LINE_TEXT);// this requires 'int i'
    prt(THIN_LINE, LEFT);
    sprintf(line, "%s %s %s", upperFirst, upperMiddle, upperLast);
    prt(line, CENTER);
    CLEAR_STRING(line, i, MAX_LINE_TEXT);
    sprintf(line, "[ DOB: %d/%d/%d ][ PID: %s ][ MRN: %s ]",
	    p->dob->month, p->dob->day, p->dob->year,
	    p->pid, p->mrn);
    prt(line, CENTER);
    prt(THICK_LINE, LEFT);
    prt("Address", CENTER);
    prt(THIN_LINE, LEFT);
    prt(p->addr->field1, CENTER);
    prt(p->addr->field2, CENTER);
    prt(p->addr->field3, CENTER);
    prt(p->addr->field4, CENTER);
    prt(THIN_LINE, LEFT);
    prt("Contact information", CENTER);
    prt(THIN_LINE, LEFT);
    CLEAR_STRING(line, i, MAX_LINE_TEXT);
    sprintf(line, "[H] %s", p->contact->phone_h);
    prt(line, CENTER);
    CLEAR_STRING(line, i, MAX_LINE_TEXT);
    sprintf(line, "[C] %s", p->contact->phone_c);
    prt(line, CENTER);
    CLEAR_STRING(line, i, MAX_LINE_TEXT);
    sprintf(line, "[W] %s", p->contact->phone_w);
    prt(line, CENTER);
    CLEAR_STRING(line, i, MAX_LINE_TEXT);
    sprintf(line, "[E] %s", p->contact->email);
    prt(line, CENTER);
    prt(THIN_LINE, LEFT);
    if (strcmp(p->emerg1->full_name, "No contact given") != 0) {
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "%s [%s]",
	      p->emerg1->full_name,
	      p->emerg1->relationship);
      prt(line, CENTER);
      prt(THIN_LINE, LEFT);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "[H] %s", p->emerg1->contact->phone_h);
      prt(line, CENTER);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "[C] %s", p->emerg1->contact->phone_c);
      prt(line, CENTER);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "[W] %s", p->emerg1->contact->phone_w);
      prt(line, CENTER);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "[E] %s", p->emerg1->contact->email);
      prt(THIN_LINE, LEFT);
    }
    if (strcmp(p->emerg2->full_name, "No contact given") != 0) {
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "%s [%s]",
	      p->emerg2->full_name,
	      p->emerg2->relationship);
      prt(line, CENTER);
      prt(THIN_LINE, LEFT);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "[H] %s", p->emerg2->contact->phone_h);
      prt(line, CENTER);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "[C] %s", p->emerg2->contact->phone_c);
      prt(line, CENTER);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "[W] %s", p->emerg2->contact->phone_w);
      prt(line, CENTER);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "[E] %s", p->emerg2->contact->email);
      prt(THIN_LINE, LEFT);
    }
  } else {
    prt("No patient information avaialble.", CENTER);
    prt(THIN_LINE, LEFT);
  }
  free(upperFirst);
  free(upperMiddle);
  free(upperLast);
}

// Create patient, populate the fields.
Patient *Add_patient()
{
  Patient *p = Patient_create();
  size_t nbytes = MAX_DATA;
  ssize_t mr = NULL;
  char *selection = malloc(sizeof(char) * 6); // quit\n\0 = 6


  check(p != NULL, "Patient was not created.");
  
  // Get patients name
  printf("PATIENTS NAME\n"
	 " First: ");
  mr = modgetl(p->name->first, &nbytes);
  printf(" Middle: ");
  mr = modgetl(p->name->middle, &nbytes);
  printf(" Last: ");
  mr = modgetl(p->name->last, &nbytes);
  
  // Get patients date of birth
  printf("\nDATE OF BIRTH (Entered as decimal number)\n"
	 " Month: ");
  mr = modgetlatoi(&p->dob->month, &nbytes);
  printf(" Day: ");
  mr = modgetlatoi(&p->dob->day, &nbytes);
  printf(" Year: ");
  mr = modgetlatoi(&p->dob->year, &nbytes);
  printf(" Personal ID (e.g. US Social Security): ");
  mr = modgetl(p->pid, &nbytes);
  
  // Get patients address
  printf("\nADDRESS\n");
  printf(" 1/4: ");
  mr = modgetl(p->addr->field1, &nbytes);
  printf(" 2/4: ");
  mr = modgetl(p->addr->field2, &nbytes);
  printf(" 3/4: ");
  mr = modgetl(p->addr->field3, &nbytes);
  printf(" 4/4: ");
  mr = modgetl(p->addr->field4, &nbytes);
  
  // Get patients contact information
  printf("\nCONTACT INFORMATION\n"
	 " Email address: ");
  mr = modgetl(p->contact->email, &nbytes);
  printf(" Home phone: ");
  mr = modgetl(p->contact->phone_h, &nbytes);
  printf(" Work phone: ");
  mr = modgetl(p->contact->phone_w, &nbytes);
  printf(" Cell phone: ");
  mr = modgetl(p->contact->phone_c, &nbytes);
  
  // Get emergency contact information
  printf("\nWould you like to add an emergency contact (y/n)? ");
  mr = modgetl(selection, &nbytes);
  if (selection[0] == 'y' || selection[0] == 'Y') {
    printf("\nEMERGENCY CONTACT #1\n");
    printf(" Name (full): ");
    mr = modgetl(p->emerg1->full_name, &nbytes);
    printf(" Relationship: ");
    mr = modgetl(p->emerg1->relationship, &nbytes);
    printf(" Email address: ");
    mr = modgetl(p->emerg1->contact->email, &nbytes);
    printf(" Home phone: ");
    mr = modgetl(p->emerg1->contact->phone_h, &nbytes);
    printf(" Work phone: ");
    mr = modgetl(p->emerg1->contact->phone_w, &nbytes);
    printf(" Cell phone: ");
    mr = modgetl(p->emerg1->contact->phone_c, &nbytes);

    printf("\nWould you like to add an another emergency contact (y/n)? ");
    mr = modgetl(selection, &nbytes);
    if (selection[0] == 'y' || selection[0] == 'Y') {
      printf("\nEMERGENCY CONTACT #2\n");
      printf(" Name (full): ");
      mr = modgetl(p->emerg2->full_name, &nbytes);
      printf(" Relationship: ");
      mr = modgetl(p->emerg2->relationship, &nbytes);
      printf(" Email address: ");
      mr = modgetl(p->emerg2->contact->email, &nbytes);
      printf(" Home phone: ");
      mr = modgetl(p->emerg2->contact->phone_h, &nbytes);
      printf(" Work phone: ");
      mr = modgetl(p->emerg2->contact->phone_w, &nbytes);
      printf(" Cell phone: ");
      mr = modgetl(p->emerg2->contact->phone_c, &nbytes);
    }
  }

  check(mr > 0, "Failed to acquire input.");

  free(selection);
  
  return p;

 error:
  return NULL;
}

Patient *Patient_copy(Patient *p)
{
  Patient *p_Pt = Patient_create();

  strcpy(p_Pt->name->first, p->name->first);
  strcpy(p_Pt->name->middle, p->name->middle);
  strcpy(p_Pt->name->last, p->name->last);
  p_Pt->dob->month = p->dob->month;
  p_Pt->dob->day = p->dob->day;
  p_Pt->dob->year = p->dob->year;
  strcpy(p_Pt->addr->field1, p->addr->field1);
  strcpy(p_Pt->addr->field2, p->addr->field2);
  strcpy(p_Pt->addr->field3, p->addr->field3);
  strcpy(p_Pt->addr->field4, p->addr->field4);
  strcpy(p_Pt->contact->phone_h, p->contact->phone_h);
  strcpy(p_Pt->contact->phone_w, p->contact->phone_w);
  strcpy(p_Pt->contact->phone_c, p->contact->phone_c);
  strcpy(p_Pt->contact->email, p->contact->email);
  strcpy(p_Pt->emerg1->full_name, p->emerg1->full_name);
  strcpy(p_Pt->emerg1->relationship, p->emerg1->relationship);
  strcpy(p_Pt->emerg1->contact->phone_h, p->emerg1->contact->phone_h);
  strcpy(p_Pt->emerg1->contact->phone_w, p->emerg1->contact->phone_w);
  strcpy(p_Pt->emerg1->contact->phone_c, p->emerg1->contact->phone_c);
  strcpy(p_Pt->emerg1->contact->email, p->emerg1->contact->email);
  strcpy(p_Pt->emerg2->full_name, p->emerg2->full_name);
  strcpy(p_Pt->emerg2->relationship, p->emerg2->relationship);
  strcpy(p_Pt->emerg2->contact->phone_h, p->emerg2->contact->phone_h);
  strcpy(p_Pt->emerg2->contact->phone_w, p->emerg2->contact->phone_w);
  strcpy(p_Pt->emerg2->contact->phone_c, p->emerg2->contact->phone_c);
  strcpy(p_Pt->emerg2->contact->email, p->emerg2->contact->email);
  strcpy(p_Pt->pid, p->pid);
  strcpy(p_Pt->mrn, p->mrn);

  return p_Pt;
}
