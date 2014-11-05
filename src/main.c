#include "interface.h"
#include "patient_add.h"

#define TRUE  1
#define FALSE 0

typedef int BOOL;

int main()
{
  ssize_t rc;
  size_t nbytes = 2;
  BOOL EXIT = FALSE;
  char *selection = malloc(sizeof(char) * 2);

  do {
    Display_main_menu();

    rc = getline(&selection, &nbytes, stdin);

    check(rc != 0, "Error acquiring input.\n"
	  "Was your input a numeric digit?\n"
	  "The program will now exit.\n");
    
    switch(selection[0]) {
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
      Display_default_warning(*selection);
      break;
    }
    
    Display_confirm_continue();
    
  } while (!EXIT);
  
  free(selection);
  
 error:
  return -1;
}
