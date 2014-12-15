// file: clinical_tools.h

#ifndef _clinical_tools_h
#define _clinical_tools_h

#include "lab_types.h"

int Calculate_anion_gap(int na, int cl, int bicarb);
double Calculate_corrected_anion_gap(int gap, double normal_alb, double alb);

#endif

// eof: clinical_tools.h
