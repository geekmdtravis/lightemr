#include <stdio.h>
#include <string.h>
#include "patient.h"

int main()
{
  Patient *p1 = Patient_create();
  BOOL rc;

  Name n1 = Set_name("Joe", "B.", "Schmoe");
  Birthdate b1 = Set_birthdate(12, 30, 1990);
  Address a1 = Set_address("1234 Rodeo Dr.", "Hollywood, CA", "90210", "");
  Contact c1 = Set_contact(5556667777, 5558886666, 3332221111,
			   "joebschmoe@gmail.com");
  Emergency_contact ec1 = Set_emergency_contact("Jan schmoe","wife",
						5556667777, 5558889999,
						0, "janaschmoe@hotmail.com");
  Emergency_contact ec2 = Set_emergency_contact("James Schmoe", "Son",
						5556667777, 5558889990,
						5554442222, "janaschmoe@hotmail.com");
  int pid = 111223333;
  int mrn = 1234567890;

  Patient_populate(p1, &n1, &b1, &a1, &c1, &ec1, &ec2, pid, mrn);

  Patient_print_info(p1);
  
  rc = Patient_destroy(p1);
  
  return (rc) ? 0 : 1;
}
