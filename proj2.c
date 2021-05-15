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

		if (!strcmp(ler_input, SET_CMD)) set_func(&order);

		if (!strcmp(ler_input, PRINT_CMD)) {
			print(order);
			printf("lido\n");
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

void set_func(link* order) {
	char buffer[MAX_SIZE];
	scanf("%s", buffer);
	*order = insertEnd(*order, buffer);

	printf("sucesso\n");
}
