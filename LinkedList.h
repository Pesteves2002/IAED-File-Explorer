#ifndef _DLINKED_H
#define _DLINKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*node que contem o valor, o anterior e o seguinte*/
/* anterior e usado para facilmente se retirar o elemento no caso de dar
 * delete*/

struct node {
	char *text;
	struct node *prev, *next;
};

typedef struct node Node;
typedef struct node *link;

void print(link head);
link NEW(char *buffer);
link insertEnd(link head, char *text);
link delete_search(link head, char *text);
void FREEnode(link t);

#endif