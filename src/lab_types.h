// file: lab_types.h

typedef struct Basic_metabolic_panel {
  int na;
  float k;
  int cl;
  int bicarb;
  int bun;
  float cr;
  int glu;
} BMP;

typedef struct Comprehensive_metabolic_panel {
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
} CMP;

// eof: lab_types.h
