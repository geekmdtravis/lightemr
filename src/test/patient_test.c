#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

#define TRUE 1
#define FALSE 0
typedef int BOOL;

int main()
{
  // Testing Patient_create
  Patient *p = NULL;
  BOOL rb;

  printf("TESTING patient.c\n\n");
  
  p = Patient_create();
  printf("Patient %s created.\n\n", (p) ? "was" : "was not");
  
  // Begin testing the update functions
  printf("Beginning testing of the update functions.\n");
  // Testing Patient_update_name
  rb = Patient_update_name(p, "James", "Joseph", "Jefferson");
  printf("%s: %s.\n", "Patient_update_name ", (rb == TRUE) ? "Update success" : "Update failure");
  // Testing Patient_update_address
  rb = Patient_update_address(p, "10234 Rodeo Drive", "Hollywood, CA", "92604", "USA");
  printf("%s: %s.\n", "Patient_update_address", (rb == TRUE) ? "Update success" : "Update failure");
  // Testing Patient_update_dob
  rb =Patient_update_dob(p, 1, 1, 1900);
  printf("%s: %s.\n", "Patient_update_dob", (rb == TRUE) ? "Update success" : "Update failure");
  // Testing Patient_update_contact
  rb = Patient_update_contact(p, "3334445555", "2223334444", "5554443333", "james.joseph@jefferson.com");
  printf("%s: %s.\n", "Patient_update_contact", (rb == TRUE) ? "Update success" : "Update failure");
  // Testing Patient_update_emergency
  rb = Patient_update_emergency(p->emerg1, "Jenny Jefferson",
				"3334443333", "5553332222",
				"2221112222", "sister", "jenny.joseph@jefferson.com");
  printf("%s: %s.\n", "Patient_update_emergency", (rb == TRUE) ? "Update success" : "Update failure");
  rb = Patient_update_emergency(p->emerg2, "Penny Jefferson",
				"3334493333", "5550332222",
				"2223112222", "sister", "penny.joseph@jefferson.com");
  printf("%s: %s.\n", "Patient_update_emergency", (rb == TRUE) ? "Update success" : "Update failure");
  // Done testing the update functions
  printf("Completed testing the update functions.\n\n");
  
  // Testing Patient_destroy()
  Patient_destroy(p);
  p = NULL;
  printf("Patient %s destroyed.\n\n", (!p) ? "was" : "was not");
  
  // Evaluate exit success
  printf("%s exited.\n\n", (!p) ? "Sucessfully" : "Unsucessfully");
  exit((!p) ? EXIT_SUCCESS : EXIT_FAILURE);

}
