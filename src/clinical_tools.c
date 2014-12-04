// file: clinical_tools.c
#include <stdio.h>
#include <stdlib.h>
#include "modstring.h"
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

int Process_anion_gap()
{
  typedef struct Basic_metabolic_panel BMP;
  BMP b;
  int rc;
  size_t nbytes = 4;
  char *userInput = malloc(sizeof(char) * nbytes);
  
  system("clear");
  printf("Anion Gap Calculator\n\n"
	 "Na\t: ");
  modgetlatoi(&b.na, &nbytes);
  printf("Cl\t: ");
  modgetlatoi(&b.cl, &nbytes);
  printf("Bicarb\t: ");
  modgetlatoi(&b.bicarb, &nbytes);

  rc = Calculate_anion_gap(b.na, b.cl, b.bicarb);
  printf("Anion gap: %d\n\n", rc);
  
  if(rc != -99) {
    printf("Would you like to calculate for hypoalbuminemia? ");
    modgetl(userInput, &nbytes);
    if(userInput[0] == 'y') {
      int gap = rc;
      double rd;
      double normalAlb;
      double alb;
      printf("Normal albumin (4.2)\t: ");
      modgetlatof(&normalAlb, &nbytes);
      printf("Observed albumin\t: ");
      modgetlatof(&alb, &nbytes);
      rd = Calculate_corrected_anion_gap(gap, normalAlb, alb);
      printf("Corrected anion gap: %.2f\n\n", rd);
    } else {
      printf("Correction will not be calculated.\n\n");
    }
    free(userInput);
    return 0;
  } else {
    printf("Result of %d indicating input error.\n\n", rc);
    free(userInput);
    return -1;
  }
}

// eof: clinical_tools.c
