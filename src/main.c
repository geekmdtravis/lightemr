#include "interface.h"
#include "patient_add.h"

#define TRUE  1
#define FALSE 0

typedef int BOOL;

int main()
{
  int rc;
  char selection;
  BOOL EXIT = FALSE;

  do {
    Display_main_menu();

    rc = fscanf(stdin, "%c", &selection);

    check(rc != 0, "Error acquiring input.\n"
	  "Was your input a numeric digit?\n"
	  "The program will now exit.\n");
    
    switch(selection) {
    case '1':
      Display_patient_lookup_menu();
      break;
      
    case '2':
      Display_patient_add_menu();
      Add_patient();
      break;
      
    case '3':
      Display_patient_remove_menu();
      break;
      
    case '4':
      Display_help_menu();
      break;
      
    case '5':
      Display_clinical_tools_menu();
      break;
      
    case '6':
      EXIT = Display_confirm_exit();
      Evaluate_exit_signal(EXIT);
      if(EXIT) return 0;
      break;
      
    default:
      Display_default_warning(selection);
      break;
    }
    
    Display_confirm_continue();
    
  } while (!EXIT);
  
 error:
  return -1;
}
