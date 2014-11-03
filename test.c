#include <stdio.h>
#include <string.h>
#include "patient.h"

int main()
{
  Patient p1;
  strcpy(p1.name.first, "Joe");
  strcpy(p1.name.middle, "B");
  strcpy(p1.name.last, "Schmoe");
  p1.dob.month = 4;
  p1.dob.day = 21;
  p1.dob.year = 1942;
  strcpy(p1.addr.field1, "1 Glenhurst");
  strcpy(p1.addr.field2, "Irvine, CA");
  strcpy(p1.addr.field3, "92604");
  strcpy(p1.addr.field4, "United States of America");
  strcpy(p1.contact.email, "joebschmoe@gmail.com");
  p1.contact.phone_h = 5555555555;
  p1.contact.phone_c = 5556665555;
  p1.contact.phone_w = 5557775555;
  p1.pid = 333221234;
  p1.mrn = 1234567890;

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
	 "MRN: %d\n",
	 p1.name.first,
	 p1.name.middle,
	 p1.name.last,
	 p1.dob.month,
	 p1.dob.day,
	 p1.dob.year,
	 p1.addr.field1,
	 p1.addr.field2,
	 p1.addr.field3,
	 p1.addr.field4,
	 p1.contact.email,
	 p1.contact.phone_h,
	 p1.contact.phone_c,
	 p1.contact.phone_w,
	 p1.pid,
	 p1.mrn);
  
  return 0;
}
