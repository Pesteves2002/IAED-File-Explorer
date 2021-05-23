
/*---------------------------2 Projeto de IAED------------------------*/
/* Tomás Esteves - ist199341*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"
#include "hashtable.h"
#include "mergesort.h"

int main() {
	char ler_input[CMD_SZ];
	link order = NULL;
	STinit(17);

	scanf("%s", ler_input);

	while (strcmp(ler_input, QUIT_CMD)) {
		if (!strcmp(ler_input, HELP_CMD))
			help_func();
		else if (!strcmp(ler_input, SET_CMD)) {
			getchar();
			set_func(&order);
		} else if (!strcmp(ler_input, PRINT_CMD)) {
			print(order);
		} else if (!strcmp(ler_input, FIND_CMD)) {
			char work[67000];
			int i;
			scanf("%s", work);
			i = strlen(work);
			while (work[--i] == '/') work[i] = '\0';
			strcpy(work, find_func(order, work));
			if (strcmp(work, "0")) printf("%s\n", work);
		} else if (!strcmp(ler_input, LIST_CMD)) {
			char work[67000];
			char c = getchar();
			int i;
			link x = order;
			int aux;
			/*se for espaco*/
			if (c != '\n') {
				scanf("%s", work);
				i = strlen(work);
				while (work[--i] == '/') work[i] = '\0';
				aux = list_func(order, work);
				if (aux) printf(NOT_FOUND);
			}
			/*dar print da raiz*/
			else {
				if (order != NULL) {
					if (x->next == NULL) {
						printf("%s\n", x->diretory);
					} else {
						link x = order;

						link alfa[1000];
						link aux[1000];
						int i = 0;
						int l;
						/*caso de ser apenas 1 valor*/
						if (x->next == NULL) {
							printf("%s\n", x->diretory);
						}

						/*ler o resto do elemento*/
						for (; x->next != NULL; x = x->next) {
							alfa[i++] = x;
						}
						/*ler o ultimo do elemento*/

						alfa[i] = x;

						mergesort(alfa, 0, i, aux);

						for (l = 0; l <= i; l++) printf("%s\n", alfa[l]->diretory);
					}
				}
			}
		} else if (!strcmp(ler_input, DELETE_CMD))

		{
			char work[67000];
			char c = getchar();
			int i;
			if (c != '\n') {
				scanf("%s", work);
				i = strlen(work);
				while (work[--i] == '/') work[i] = '\0';
				order = delete_func(order, work);
			} else {
				order = aux_delete(order);
			}
		} else if (!strcmp(ler_input, SEARCH_CMD)) {
			char value[66000];
			link res;
			int i = 0;
			char c;
			getchar();

			while ((c = getchar()) != '\n') value[i++] = c;

			value[i] = '\0';

			res = STsearch(value);

			if (res != NULL) {
				printf("%s/%s\n", res->fullpath, res->diretory);
			} else
				printf(NOT_FOUND);
		}
		scanf("%s", ler_input);
	}
	apagar(&order);
	STfree();

	return 0;
}