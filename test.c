#include <stdio.h>
#include <string.h>
#include "patient.h"

int main()
{
  Patient *p1 = Patient_create();
  BOOL rc;

  Name n1;
  Birthdate b1;
  Address a1;
  Contact c1;
  Emergency_contact ec1;
  int pid = 111223333;
  int mrn = 1234567890;

  Patient_populate(p1, NULL, NULL, NULL, NULL, NULL, NULL, pid, mrn);

  printf("\n\n");
  
  printf("Full name: %s %s %s\n"
	 "DOB: %d/%d/%d\n"
	 "Address:\n"
	 " %s\n"
	 " %s\n"
	 " %s\n"
	 " %s\n"
	 "Email: %s\n"
	 "Home Phone: %ld\n"
	 "Cell Phone: %ld\n"
	 "Work Phone: %ld\n"
	 "Personal ID: %d\n"
	 "MRN: %d\n"
	 "Emergency Conact: %s\n"
	 "Emergency Number: %ld\n",
	 p1->name.first,
	 p1->name.middle,
	 p1->name.last,
	 p1->dob.month,
	 p1->dob.day,
	 p1->dob.year,
	 p1->addr.field1,
	 p1->addr.field2,
	 p1->addr.field3,
	 p1->addr.field4,
	 p1->contact.email,
	 p1->contact.phone_h,
	 p1->contact.phone_c,
n	 p1->contact.phone_w,
	 p1->pid,
	 p1->mrn,
	 p1->emerg1.full_name,
	 p1->emerg1.contact.phone_h);
  
  rc = Patient_destroy(p1);
  
  return (rc) ? 0 : 1;
}
