// file: login.h
#ifndef _login_h
#define _login_h

#include <stdio.h>
#include <stdlib.h>
#include "modstring.h"
#include "dbg.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MAX_TRIES 5

void Prompt_user(void);
void Prompt_pass(void);
int User_login(void);

#endif
// eof: login.h
