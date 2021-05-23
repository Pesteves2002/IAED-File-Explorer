#ifndef COMMANDS_H
#define COMMANDS_H

#define HELP_CMD "help"
#define QUIT_CMD "quit"
#define SET_CMD "set"
#define PRINT_CMD "print"
#define FIND_CMD "find"
#define LIST_CMD "list"
#define SEARCH_CMD "search"
#define DELETE_CMD "delete"

#define HELP_ACTION "help: Imprime os comandos disponíveis."
#define QUIT_ACTION "quit: Termina o programa."
#define SET_ACTION "set: Adiciona ou modifica o valor a armazenar."
#define PRINT_ACTION "print: Imprime todos os caminhos e valores."
#define FIND_ACTION "find: Imprime o valor armazenado."
#define LIST_ACTION \
	"list: Lista todos os componentes imediatos de um sub-caminho."
#define SEARCH_ACTION "search: Procura o caminho dado um valor."
#define DEL_ACTION "delete: Apaga um caminho e todos os subcaminhos."

#define NOT_FOUND "not found\n"
#define NO_DATA "no data\n"

#define NUM_CMD 8
#define CMD_SZ 10
#define MAX_SIZE 66666

struct node {
	/*stores the directory*/
	char *diretory;
	/*stores the value*/
	char *value;
	/*stores the path of the directories above*/
	char *fullpath;
	/*points to next directory */
	struct node *next;
	/*points to the directory below*/
	struct node *abaixo;
};

typedef struct node Node;
typedef struct node *link;

void help_func();

void set_func(link *order);

/*auxiliar function to insert or change an element*/
link insertEnd(link head, char path[]);

/*auxiliar function that creates a new folder*/
link criar_folder(char *dir, char path[]);

/*auxiliar function that creates the last folder*/
link criar_folder_final(char *dir, char path[]);

void print(link head);

char *find_func(link order, char *word);

int list_func(link head, char *word);

link delete_func(link head, char *path);

/*auxiliar function that deletes and frees the memory of the folders*/
link aux_delete(link head);

/*auxiliar function that deletes the whole list of folders*/
void apagar(link *head);

#endif