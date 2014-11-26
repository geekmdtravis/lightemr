// file: test.c
#include "login.h"

int main()
{
  int rc;
  rc = User_login();

  exit((rc == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}
// eof: test.c
