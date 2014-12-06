// file: clinical_tools.c
#include <stdio.h>
#include <stdlib.h>
#include "modstring.h"
#include "clinical_tools.h"
#include "interface.h"

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
  int rc, i;
  int gap;
  double rd;
  double normalAlb;
  double alb;
  size_t nbytes = 4;
  char *userInput = malloc(sizeof(char) * nbytes);
  void (*prt)(char *input, int align) = Print_interface_line;
  char line[MAX_LINE_TEXT];
  
  system("clear");
  prt(THIN_LINE, LEFT);
  prt("LightEMR: Anion Gap Calculator", CENTER);
  prt(THICK_LINE, LEFT);
  fprintf(stdout, "%s", "  Sodium  : ");
  modgetlatoi(&b.na, &nbytes);
  fprintf(stdout, "%s", "  Chloride: ");
  modgetlatoi(&b.cl, &nbytes);
  fprintf(stdout, "%s", "  Bicarb  : ");
  modgetlatoi(&b.bicarb, &nbytes);

  rc = Calculate_anion_gap(b.na, b.cl, b.bicarb);
  prt(THIN_LINE, LEFT);
  CLEAR_STRING(line, i, MAX_LINE_TEXT);
  sprintf(line, "Anion gap: %d", rc);
  prt(line, CENTER);
  CLEAR_STRING(line, i, MAX_LINE_TEXT);
  sprintf(line, "(%d - (%d + %d))", b.na, b.cl, b.bicarb);
  prt(line, CENTER);
  prt(THIN_LINE, LEFT);
  
  if(rc != -99) {
    printf("  Would you like to calculate for hypoalbuminemia (y/n)? ");
    modgetl(userInput, &nbytes);
    switch(userInput[0]) {
    case 'Y':
    case 'y':
      gap = rc;
      printf("  Normal albumin (4.2): ");
      modgetlatof(&normalAlb, &nbytes);
      printf("  Observed albumin    : ");
      modgetlatof(&alb, &nbytes);
      rd = Calculate_corrected_anion_gap(gap, normalAlb, alb);
      prt(THIN_LINE, LEFT);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "Corrected anion gap: %.2f", rd);
      prt(line, CENTER);
      CLEAR_STRING(line, i, MAX_LINE_TEXT);
      sprintf(line, "(%.2f x (%.2f - %.2f))", 2.5, normalAlb, alb);
      prt(line, CENTER);
      prt(THIN_LINE, LEFT);
      break;
      
    case 'N':
    case 'n':
      prt(THIN_LINE, LEFT);
      prt("Correction will not be calculated.  ", CENTER);
      prt(THIN_LINE, LEFT);
      break;

    default:
      prt(THIN_LINE, LEFT);
      prt("  Incorrect selection. You will be returned to the main menu.", LEFT);
      prt(THIN_LINE, LEFT);
      return -1;
      break;
    }
    free(userInput);
    return 0;
  } else {
    prt(THIN_LINE, LEFT);
    CLEAR_STRING(line, i, MAX_LINE_TEXT);
    sprintf(line, "  Result of %d indicating input error.\n\n", rc);
    prt(line, LEFT);
    prt(THIN_LINE, LEFT);
    free(userInput);
    return -1;
  }
}

// eof: clinical_tools.c
