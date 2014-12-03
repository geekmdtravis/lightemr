#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/clinical_tools.h"

void Print_usage(void);

int main(int argc, char *argv[])
{
  if (argc < 4 || argc > 5) {
    Print_usage();
    exit(EXIT_FAILURE);
  }

  int na = atoi(argv[1]);
  int cl = atoi(argv[2]);
  int bicarb = atoi(argv[3]);
  int ag = Calculate_anion_gap(na, cl, bicarb);

  printf("Anion gap: %d%s\n", ag,
	 ((argc == 4) ? "\nIf hypoalbuminemia exists, this should be corrected." : ""));
  
  if (argc == 5) {
    double alb = atof(argv[4]);
    double cg = Calculate_corrected_anion_gap(ag, 4.2, alb);
    printf("Corrected gap: %.2f\n", cg);
  }

  exit(EXIT_SUCCESS);
  
}

void Print_usage()
{
  printf("USAGE: [1] ./aniongap [na] [cl] [bicarb]\n"
	 "       [2] ./aniongap [na] [cl] [bicarb] [albumin]\n"
	 "\n"
	 "EXAMPLE: [1] ./aniongap 143 105 24\n"
	 "         [2] ./aniongap 143 105 24 4.2\n"
	 "\n"
	 "Expected normal range: 3 mEq/L to 11 mEq/L\n"
	 "\n"
	 "Gap acidosis: MUDPILES\n"
	 "\tMethanol\n"
	 "\tUremia\n"
	 "\tDiabetic ketoacidosis\n"
	 "\tIsoniazid\n"
	 "\tPropylene glycol\n"
	 "\tIsoniazid / Iron\n"
	 "\tLactic acidosis\n"
	 "\tEthylene glycol\n"
	 "\tSalicylates\n"
	 "\n"
	 "Non-gap acidosis: HARDUPS\n"
	 "\tHyperalimentation\n"
	 "\tAcetazolamide (and other carbonic anhydrase inhibitors)\n"
	 "\tRenal tubular acidosis\n"
	 "\tDiarrhea\n"
	 "\tUreteroenteric fistula\n"
	 "\tPancreaticoduodenal fistula\n"
	 "\tSpironolactone\n"
	 "\n"
	 "Negative gap: Consider multiple myeloma\n"
	 "\n");
}
