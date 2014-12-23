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


// Note sure why I need to re-define everything.
typedef struct Patient Patient;
typedef struct Note Note;
typedef struct Patient_query_node PQ_node;
typedef struct Note_query_node NQ_node;

// Used in the Print_interface_line function
typedef enum {LEFT, RIGHT, CENTER } align_t;

/****************************************************
 * Print_interface_line(char *input, align_t align)
 ****************************************************
 * A formatted line of max 80 chars wide used as a
 * simple method to standardize the display interface.
 * Nothing is returned.
****************************************************/
void Print_interface_line(char *input, align_t align);

/************************************************
 * Formatted_date()
 ************************************************
 * Return a string literal with the date formatted
 * as MO/DY/YR HR:MIN:SEC
 * This is on the heap and needs to be freed later
 ***********************************************/
char *Formatted_date(void);

/***************************************************
 * Display_main_menu(void)
 ***************************************************
 * Just as it sounds, displays the main menu. No return.
 **************************************************/
void Display_main_menu(void);

/****************************************
 * Display_patient_lookup_menu()
 ****************************************
 * As it suggests, displays the menu
 * for the patient lookup function.
 ****************************************/
void Display_patient_lookup_menu(void);

/***************************************************
 * Process_patient_lookup(Patient **pt, sqlite *db)
 ***************************************************
 * Called from main when user selects option to
 * initiate the process of looking up a patient.
 * Returns 0 for success and -1 for no patient found.
 ***************************************************/
int Process_patient_lookup(Patient **pt, sqlite3 *db);

/*****************************************
 * Display_patient_portal_menu(Patient *pt)
 *****************************************
 * After a patient is selected, the user
 * is directed to the patient portal. This,
 * as it suggests, is to show the menu for
 * the user.
 *****************************************/
void Display_patient_portal_menu(Patient *p);

/***********************************************
 * Process_patient_portal_selection(Patient *pt)
 ***********************************************
 * Once patient is at the Patient Portal, this
 * is where the patient selects what they would
 * like to do with this patients medical record.
 * Calls the functions necessary to go to the
 * next step into the patient portal. E.g.
 * to add a note, or lookup a note.
 * Returns -1 if patient makes in inappropriate
 * selection, 0 after successful selection
 * is made.
 **********************************************/
int Process_patient_portal_selection(Patient *pt);

void Display_notes_menu(Patient *pt);
int Process_notes_selection(Patient *pt);
void Display_note(Note *n, Patient *pt);
void Display_note_type(void);
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



