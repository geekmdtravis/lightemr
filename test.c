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

  printf("Full name: %s %s %s\n"
	 "DOB: %d/%d/%d\n",
	 p1.name.first,
	 p1.name.middle,
	 p1.name.last,
	 p1.dob.month,
	 p1.dob.day,
	 p1.dob.year);
  
  return 0;
}
