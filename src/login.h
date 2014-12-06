// file: login.h
#ifndef _login_h
#define _login_h

#include <stdio.h>
#include <stdlib.h>
#include "modstring.h"
#include "dbg.h"
#include "defs.h"

#define MAX_TRIES 5

void Display_welcome(void);
int User_login(void);

#endif
// eof: login.h
