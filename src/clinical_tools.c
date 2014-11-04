// file: clinical_tools.c

#include "clinical_tools.h"

int Calculate_anion_gap(int na, int cl, int bicarb)
{
  // set very low cutoffs for real values being passed
  // to the calculator.
  // success returns AG
  // failure returns -1
  return (na > 90 && cl > 70 && bicarb > 0) ?
    (na - (cl + bicarb)) : -1;
}

// eof: clinical_tools.c
