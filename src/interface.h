// file: interface.h
#include "patient.h"
#include "database.h"
#include "stdio.h"
#include "modstring.h"
#include "dbg.h"

typedef int BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef _interface_h
#define _interface_h

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "version.h"

void Display_main_menu(void);
void Display_patient_lookup_menu(void);
int Process_patient_lookup(char *selection, Patient *pt, sqlite3 *db);
void Display_patient_add_menu(void);
void Display_patient_remove_menu(void);
void Display_help_menu(void);
void Display_clinical_tools_menu(void);
void Display_billing_menu(void);
void Display_confirm_continue(void);
int Display_confirm_exit(void);
void Evaluate_exit_signal(int exit);
void Display_default_warning(char selection);

#endif



