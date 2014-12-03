// file: clinical_tools.h

#ifndef _clinical_tools_h
#define _clinical_tools_h

typedef int BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

struct Basic_metabolic_panel {
  int na;
  float k;
  int cl;
  int bicarb;
  int bun;
  float cr;
  int glu;
};

struct Comprehensive_metabolic_panel {
  int na;
  float k;
  int cl;
  int bicarb;
  int bun;
  float cr;
  int glu;
  float calcium;
  float protein;
  float albumin;
  int alkphos;
  float tbili;
  int ast;
  int alt;
};
  

#include <stdio.h>

int Calculate_anion_gap(int na, int cl, int bicarb);
double Calculate_corrected_anion_gap(int gap, double normal_alb, double alb);
int Process_anion_gap(void);

#endif

// eof: clinical_tools.h
