#include "interface.h"
#include "patient.h" 
#include "patient_add.h"

#ifndef TRUE
#define TRUE  1
#endif

#ifndef TRUE
#define FALSE 0
#endif

typedef int BOOL;

int main()
{
  ssize_t rc = 0;
  size_t nbytes = 2;
  BOOL EXIT = FALSE;
  char *selection = malloc(sizeof(char) * 2);
  Patient *pt = NULL;

  do {
    Display_main_menu();

    rc = getline(&selection, &nbytes, stdin);
    check(rc != 0, "Error acquiring input.\n"
	  "Was your input a numeric digit?\n"
	  "The program will now exit.\n");
    
    switch(selection[0]) {
    case '1':
      Display_patient_lookup_menu();
      // This is only temporary. Clearly not
      // the final implementation.
      if(pt) Patient_print_info(pt);
      else printf("No patient selected.\n\n");
      break;
      
    case '2':
      Display_patient_add_menu();
      if(pt) Patient_destroy(pt);
      pt = Add_patient();
      // need to generate MRN
      // need to save patient to database
      break;
      
    case '3':
      Display_patient_remove_menu();
      if(pt) {
	Patient_destroy(pt);
	printf("Patient has been removed.\n\n");
	pt = NULL;
      } else {
	printf("No active patients.\n\n");
      }
      break;
      
    case '4':
      Display_help_menu();
      break;
      
    case '5':
      Display_clinical_tools_menu();
      break;
      
    case '6':
      Display_billing_menu();
      break;
      
    case '7':
      EXIT = Display_confirm_exit();
      Evaluate_exit_signal(EXIT);
      if(EXIT){
	if(selection) free(selection);
	if(pt) Patient_destroy(pt);
	return 0;
      }
      break;
      
    default:
      Display_default_warning(*selection);
      break;
    }
    
    Display_confirm_continue();
    
  } while (!EXIT);
  
 error:
  return -1;
}
