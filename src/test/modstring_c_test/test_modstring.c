#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "modstring.h"

int main()
{
  printf("TESTING modstring.c\n\n");
  char *testString = malloc(sizeof(char) * 30);
  strcpy(testString, "This is a test 1, 2, 3.");
  char *compString = malloc(sizeof(char) * 30);
  strcpy(compString, "This is a test 1, 2, 3");

  printf("Before:\n"
	 "%s\n"
	 "%s\n\n",
	 testString,
	 compString);
  trim(testString);
  printf("After:\n"
	 "%s\n"
	 "%s\n\n",
	 testString,
	 compString);

  // Testing a character array
  char testStr[10];
  testStr[0] = 'a';
  testStr[1] = 'b';
  testStr[2] = '\n';
  testStr[3] = '\0';
  printf("Before the trim: %s\n", testStr);
  trim(testStr);
  printf("After the trim: %s\n", testStr);

  if(testString != NULL) {
    free(testString);
    testString = NULL;
  }
  if(compString != NULL) {
    free(compString);
    compString = NULL;
  }

  printf("Testing modgetl.\n\n");
#define MAXDATA 100
  // Allocate 50 bytes to the input string inpString
  char *inpString = malloc(sizeof(char) * MAXDATA);
  size_t nbytes = MAXDATA;
  ssize_t rc;
  printf("Enter a name: ");
  rc = modgetl(inpString, &nbytes);
  // rc = getline(&inpString, &nbytes, stdin);
  printf("\n\nValue of rc:%zd | You entered: %s.\n", rc, inpString);
  free(inpString);
  inpString = NULL;

  exit(EXIT_SUCCESS);
}
