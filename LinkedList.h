#ifndef _DLINKED_H
#define _DLINKED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*node que contem o valor, o anterior e o seguinte*/
/* anterior e usado para facilmente se retirar o elemento no caso de dar
 * delete*/

typedef struct node {
	char *diretory;
	char *value;
	struct node *next;
	struct node *abaixo;
} * link;

link NEW_Node(char *buffer);
link insertEnd(link head);
link criar_folder_final(char *dir);
link criar_folder(char *dir);
void print(link head, char *path, int cond);
char *find_func(link order, char *word);
int list_func(link head, char *word);

#endif