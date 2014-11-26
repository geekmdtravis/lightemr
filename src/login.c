// file: login.c
#include "login.h"

void Prompt_user()
{
  printf("USERNAME: ");
}

void Prompt_pass()
{
  printf("PASSWORD: ");
}

int User_login()
{
  ssize_t rc;
  size_t nbytes = 100;
  int tryCount = 0;
  int access_granted = FALSE;
  int invalid_user = TRUE;
  char *username = malloc(sizeof(char) * nbytes);
  char *user_comp = "travis";
  char *password = malloc(sizeof(char) * nbytes);
  char *pass_comp = "pass1";

  // The user has MAX_TRIES attempts at a username
  while (tryCount < MAX_TRIES && invalid_user) {
    if (tryCount != 0){
      printf("Username %s was not found."
	     "You have %d attempts remaining.\n", username, (MAX_TRIES - tryCount));
    }
    // Prompt for username
    Prompt_user();
    rc = modgetl(username, &nbytes);
    check(rc != 0, "Input error.");
    // If person is defined user, prompt for pass
    if (strcmp(username, user_comp) == 0) {
      Prompt_pass();
      rc = modgetl(password, &nbytes);
      check(rc != 0, "Input error.");
      // If pass matches, grant access
      if (strcmp(password, pass_comp) == 0 ) {
	printf("Login access granted!\n");
	invalid_user = FALSE;
	access_granted = TRUE;
      } else { // Else do not grant access
	printf("Password incorrect.\n");
      }
    } else {
      tryCount += 1;
    }
    printf("\n");
  }

  free(username);
  free(password);
  
  if (tryCount == MAX_TRIES) printf ("You tried too many times. Goodbye.\n");
		       
  return (!invalid_user && access_granted) ? 0 : -1;

 error:
  return -1;
}

// eof: login.c
