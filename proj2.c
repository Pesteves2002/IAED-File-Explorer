#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

#define HELP_CMD "help"
#define QUIT_CMD "quit"
#define SET_CMD "set"
#define PRINT_CMD "print"
#define FIND_CMD "find"
#define LIST_CMD "list"
#define SEARCH_CMD "search"
#define DELETE_CMD "delete"

#define HELP_ACTION "help: Imprime os comandos disponíveis."
#define QUIT_ACTION "quit: Termina o programa"
#define SET_ACTION "set: Adiciona ou modifica o valor a armazenar."
#define PRINT_ACTION "print: Imprime todos os caminhos e valores."
#define FIND_ACTION "find: Imprime o valor armazenado."
#define LIST_ACTION "list: Lista todos os componentes de um caminho."
#define SEARCH_ACTION "search: Procura o caminho dado um valor."
#define DEL_ACTION "delete: Apaga um caminho e todos os subcaminhos."

#define NUM_CMD 8
#define CMD_SZ 10
#define MAX_SIZE 66666

void help_func();
void set_func(link* order);

int main() {
	char ler_input[CMD_SZ];
	link order = NULL;
	scanf("%s", ler_input);

	while (strcmp(ler_input, QUIT_CMD)) {
		if (!strcmp(ler_input, HELP_CMD)) help_func();

		if (!strcmp(ler_input, SET_CMD)) {
			getchar();
			set_func(&order);
		}

		if (!strcmp(ler_input, PRINT_CMD)) {
			char path[67000] = {0};
			print(order, path, 0);
		}

		if (!strcmp(ler_input, FIND_CMD)) {
			char work[67000] = {0};
			int i;
			scanf("%s", work);
			i = strlen(work);
			while (work[--i] == '/') work[i] = '\0';
			strcpy(work, find_func(order, work));
			if (strcmp(work, "0")) printf("%s\n", work);
		}

		if (!strcmp(ler_input, LIST_CMD)) {
			char work[67000] = {0};
			char c = getchar();
			int i;
			link x = order;
			if (c != '\n') {
				scanf("%s", work);
				i = strlen(work);
				while (work[--i] == '/') work[i] = '\0';
				if ((list_func(order, work))) printf("not found\n");
			} else

					if (x->next == NULL) {
				printf("%s\n", x->diretory);
			} else {
				/*ler o resto do elemento*/
				for (; x->next != NULL; x = x->next) {
					printf("%s\n", x->diretory);
				}
				/*ler o ultimo do elemento*/

				printf("%s\n", x->diretory);
			}
		}

		scanf("%s", ler_input);
	}

	return 0;
}

void help_func() {
	char* list[NUM_CMD] = {
			HELP_ACTION, QUIT_ACTION, SET_ACTION,    PRINT_ACTION,
			FIND_ACTION, LIST_ACTION, SEARCH_ACTION, DEL_ACTION,
	};
	int i;

	for (i = 0; i < NUM_CMD; ++i) {
		printf("%s\n", list[i]);
	}
}

void set_func(link* order) { *order = insertEnd(*order); }
