// file: test.c
#include "login.h"

int main()
{
  ssize_t rc;
  size_t nbytes = 100;
  int tryCount = 0;
  int invalid_user = 1;
  char *username = malloc(sizeof(char) * nbytes);
  char *user_comp = "travis";
  char *password = malloc(sizeof(char) * nbytes);
  char *pass_comp = "pass1";
  
  while (tryCount < 3 && invalid_user) {
    if (tryCount != 0){
      printf("Username %s was not found."
	     "You have %d attempts remaining.\n", username, 3-tryCount);
    }

    Prompt_user();
    rc = modgetl(username, &nbytes);
    if (strcmp(username, user_comp) == 0) {
      Prompt_pass();
      rc = modgetl(password, &nbytes);
      if (strcmp(password, pass_comp) == 0 ) {
	printf("Login access granted!\n");
	invalid_user = 0;
      } else {
	printf("Password incorrect.\n");
      }
    } else {
      tryCount += 1;
    }
  }

  free(username);
  free(password);
  exit(EXIT_SUCCESS);
}
// eof: test.c
