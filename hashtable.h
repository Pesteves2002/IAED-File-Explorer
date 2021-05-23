#ifndef _HTABLE_H
#define _HTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"

void STinit(int m);
void STinsert(link p);
link STsearch(char *v);
void STdelete(link p);
void STfree();
int hashU(char *v, int M);
void expand();

#endif