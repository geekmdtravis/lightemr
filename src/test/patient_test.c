#include <stdio.h>
#include <stdlib.h>
#include "patient.h"

int main(int argc, char *argv[])
{
  // Testing Patient_create && Patient_destroy
  Patient *p = NULL;
  p = Patient_create();
  if(p) {
    printf("Patient was created.\n");
  } else {
    printf("Patient was not created.\n");
  }
  Patient_destroy(p);
  p = NULL;
  if(p) {
    printf("Patient was not destroyed.\n");
  } else {
    printf("Patient was destroyed.\n");
  }

  // Evaluate exit success
  if(!p){
    printf("Exiting successfully.\n");
    exit(EXIT_SUCCESS);
  } else {
    printf("Failing to exist successfully.\n");
    exit(EXIT_FAILURE);
  }
}
