#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void help_func();

int main() {
	char ler_input[CMD_SZ];

	scanf("%s", ler_input);

	while (strcmp(ler_input, QUIT_CMD)) {
		if (!strcmp(ler_input, HELP_CMD)) help_func();

		scanf("%s", ler_input);
	}

	return 0;
}

void help_func() {
	char *list[NUM_CMD] = {
			HELP_ACTION, QUIT_ACTION, SET_ACTION,    PRINT_ACTION,
			FIND_ACTION, LIST_ACTION, SEARCH_ACTION, DEL_ACTION,
	};
	int i;

	for (i = 0; i < NUM_CMD; ++i) {
		printf("%s\n", list[i]);
	}
}

/*

LinkedList (talvez double, ou ent tens de guardar ponteiro para o fim) -
adicionar ao criar, para usar no print
Binary Tree para ordenação por ordem alfabética
Hashtable (ainda n sei bem se vai dar por causa da ordenacao)

*/