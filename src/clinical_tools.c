// file: clinical_tools.c
#include "clinical_tools.h"

int Calculate_anion_gap(int na, int cl, int bicarb)
{  
  return (na > 0 && cl > 0 && bicarb > 0) ?
    (na - (cl + bicarb)) : -99;
}

double Calculate_corrected_anion_gap(int gap, double normal_alb, double alb)
{
  return (normal_alb > 0 && alb > 0) ? (gap + (2.5 * (normal_alb - alb))) : -1;
}


// eof: clinical_tools.c
