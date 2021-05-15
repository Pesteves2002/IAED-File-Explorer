
#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função auxiliar responável por alocar memória para
tudo o que é necessário para um novo nó */

link NEW_Node(char *buffer) {
	link x = (link)malloc(sizeof(struct node));
	/*reservar memória para novo nó*/
	/*reservar memória para nova string*/
	x->text = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));

	strcpy(x->text, buffer);
	x->next = NULL;
	return x;
}

/*funcao usada para inserir no final*/
link insertEnd(link head, char *text) {
	link x;
	if (head == NULL) {
		return NEW_Node(text);
	}
	for (x = head; x->next != NULL;
	     x = x->next) /*loop para chegar ao fim da lista*/
		;
	x->next = NEW_Node(text); /*recorrer à função new*/
	return head;
}

/*funcao que elimina com procura*/
link delete_search(link head, char *text) {
	link t, prev;
	for (t = head, prev = NULL; t != NULL; prev = t, t = t->next) {
		if (strcmp(t->text, text) == 0) {
			if (t == head)
				head = t->next;
			else
				prev->next = t->next;
			FREEnode(t);

			break;
		}
	}
	return head;
}

/*funcao auxiliar para remover o no na operacao delete e sair do programa*/
void FREEnode(link t) {
	free(t->text);
	free(t);
}

/* funcao para dar print de tudo por ordem alfabetica*/
void print(link head) {
	link t;
	for (t = head; t != NULL; t = t->next) printf("%s\n", t->text);
}
