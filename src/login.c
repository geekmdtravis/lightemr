// file: login.c
#include "login.h"

// to do: add database support so  users and their passwords can be stored.
// also encrypt passwords as follows:
// - Randomly allocate two key ASCII characters to be appended to the front of pass
// - take their product and multiply it each letter, creating a new value . Each new
//   value will be separated by a 'a' through 'Z' depending on number of characters
//   where an additional char is inserted for each letter. So, an example might be:
//   password: pass -->
//      - append r4 to the beginning and multipy it it out
//      - 114*52* each(112 | 97 | 115 | 115)
//   encrypted password: r4663936a575016b681720c681720d

int User_login()
{
  ssize_t rc;
  size_t nbytes = 100;
  int tryCount = 1;
  int access_granted = FALSE;
  int invalid_user = TRUE;
  char *username = malloc(sizeof(char) * nbytes);
  char *user_comp = "travis";
  char *password = malloc(sizeof(char) * nbytes);
  char *pass_comp = "pass1";

  Display_welcome();

  // The user has MAX_TRIES attempts at a username
  while (tryCount <= MAX_TRIES && invalid_user) {
    // Prompt for username
    fprintf(stdout, "%s", "  User name: ");
    rc = modgetl(username, &nbytes);
    check(rc != 0, "Input error.");
    // If person is defined user, prompt for pass
    if (strcmp(username, user_comp) == 0) {
      while (tryCount <= MAX_TRIES && invalid_user) {
	fprintf(stdout, "%s", "  Password : ");
	rc = modgetl(password, &nbytes);
	check(rc != 0, "Input error.");
	// If pass matches, grant access
	if (strcmp(password, pass_comp) == 0 ) {
	  fprintf(stdout, "%s", "  Login access granted!\n");
	  invalid_user = FALSE;
	  access_granted = TRUE;
	} else { // Else do not grant access
	  fprintf(stdout, "  Password incorrect. "
		  "You have %d attempts remaining.\n",  (MAX_TRIES - tryCount));
	}
	tryCount++;
      }
    } else {
      fprintf(stdout, "  Username '%s' was not found. You have %d attempts remaining.\n",
	     username, (MAX_TRIES - tryCount));
    }
    tryCount++;
  }

  free(username);
  free(password);
  
  return (!invalid_user && access_granted) ? 0 : -1;

 error:
  return -1;
}

void Display_welcome()
{
  void (*prt)(char *intput, int align) = Print_interface_line;
  
  system("clear");
  prt(THICK_LINE, LEFT);
  prt("LightEMR: User Login Credentials Required", CENTER);
  prt(THIN_LINE, LEFT);
}


// eof: login.c
