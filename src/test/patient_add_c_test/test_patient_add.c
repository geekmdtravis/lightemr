#include <stdio.h>
#include <stdlib.h>
#include "patient_add.h"

void main()
{
  Patient *p;

  p = Add_patient();

  Patient_destroy(p);
  
  return;
}
