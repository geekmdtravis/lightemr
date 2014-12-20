// file: interface.h

#ifndef _interface_h
#define _interface_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "database.h"
#include "modstring.h"
#include "dbg.h"
#include "defs.h"
#include "clinical_tools.h"
#include "version.h"
#include "defs.h"
#include "patient.h"
#include "note.h"

typedef struct Patient Patient;
typedef struct Note Note;
typedef struct Patient_query_node PQ_node;
typedef struct Note_query_node NQ_node;

typedef enum {LEFT, RIGHT, CENTER } align_t;

void Print_interface_line(char *input, align_t align);
void Display_main_menu(void);
char *Formatted_date(void);
void Display_patient_lookup_menu(void);
int Process_patient_lookup(Patient **pt, sqlite3 *db);
void Display_patient_portal_menu(Patient *p);
int Process_patient_portal_selection(Patient *pt);
void Display_notes_menu(Patient *pt);
int Process_notes_selection(Patient *pt);
void Display_note(Note *n, Patient *pt);
int Patient_add_commit(Patient *p);
void Display_patient_add_menu(void);
void Display_patient_remove_menu(void);
void Display_help_menu(void);
void Display_clinical_tools_menu(void);
void Process_clinical_tools_menu(void);
int Process_anion_gap(void);
void Display_billing_menu(void);
void Display_confirm_continue(void);
int Display_confirm_exit(void);
void Evaluate_exit_signal(int exit);
void Display_default_warning(char selection);
int Lookup_result_selection(PQ_node *head, char *identifier);
int Lookup_notes_result_selection(NQ_node *head, char *identifier);
  
#endif



