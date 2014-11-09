// file: dbtest.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "patient.h"
#include "database.h"

int main()
{
  Patient *p = Patient_create();
  p->init = Patient_populate;
  Name n = {.first = "Travis", .middle = "Robert", .last = "Nesbit" };
  Birthdate b = {.month = 6, .day = 29, .year = 1983};
  Address a = {.field1 = "1 Glenhurst",
	       .field2 = "Irvine, CA",
	       .field3 = "92604-9042",
	       .field4 = "United States of America" };
  Contact c = {.phone_h = "9518138895", .phone_c = "9518138895",
	       .phone_w = "7144567890", .email = "tnesbit450@gmail.com" };
  Emergency_contact ec1 = { .full_name = "Jennifer T. Baker-Nesbit",
			   .relationship = "Wife",
			   .contact.phone_h = "9512970019",
			   .contact.phone_c = "9512970019",
			   .contact.phone_w = "",
			   .contact.email = "cashewsmama@gmail.com" };
   Emergency_contact ec2 = { .full_name = "Jennifer T. Baker-Nesbit",
			   .relationship = "Wife",
			   .contact.phone_h = "9512970019",
			   .contact.phone_c = "9512970019",
			   .contact.phone_w = "",
			   .contact.email = "cashewsmama@gmail.com" };
   p->init(p, &n, &b, &a, &c, &ec1, &ec2, "111222333", "1234567890");

   Patient_print_info(p);

  exit(EXIT_SUCCESS);
}

// eof: dbtest.c
