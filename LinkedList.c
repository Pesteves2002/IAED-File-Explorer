
#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* funcao para dar print de tudo por ordem de cricao*/
void print(link head, char *path, int cond) {
	link t;
	for (t = head; t != NULL; t = t->next) {
		if (t->abaixo == NULL) {
			printf("%s", path);
			printf("/%s %s\n", t->diretory, t->value);
		} else {
			if (t->value != NULL) {
				printf("%s", path);
				printf("/%s %s\n", t->diretory, t->value);
			}
			strcat(path, "/");
			strcat(path, t->diretory);
			print(t->abaixo, path, 1);
		}
		if (!cond) strcpy(path, "");
	}
}

/*funcao usada para inserir no final*/
link insertEnd(link head) {
	link x;
	char dir[1000];
	char c;
	int i = 0;

	/*obter a proxima diretoria */
	while ((c = getchar()) != '/' && c != ' ') {
		dir[i++] = c;
	}
	dir[i] = '\0';
	/*caso de ser vazia*/
	if (head == NULL) {
		if (c == ' ') return criar_folder_final(dir);

		/*se houver tab, criamos um folder*/
		return criar_folder(dir);
	}

	/*verificar quando chega ao fim da lista*/
	for (x = head; x->next != NULL; x = x->next) {
		/*se forem iguais chama para a mesma diretoria */
		if (!strcmp(x->diretory, dir)) {
			printf("aqui\n");
			/*adicionar funcao para junatar*/
			return head;
		}
	}
	if (c == ' ') x->next = criar_folder_final(dir);
	/*se houver tab, criamos um folder*/
	else
		x->next = criar_folder(dir); /*recorrer à função new*/
	return head;
}

/*atribui valor final*/
link criar_folder_final(char *dir) {
	char c;
	char valor[2000];
	int i = 0;
	link new = (link)malloc(sizeof(link));

	new->diretory = (char *)malloc(sizeof(char) * (strlen(dir) + 1));
	strcpy(new->diretory, dir);

	while ((c = getchar()) != '\n' && c != EOF) {
		valor[i++] = c;
	}
	valor[i] = '\0';

	new->value = (char *)malloc(sizeof(char) * (strlen(valor) + 1));
	strcpy(new->value, valor);

	new->abaixo = NULL;
	new->next = NULL;

	return new;
}

link criar_folder(char *dir) {
	char c;
	char new_dir[2000];
	int i = 0;

	link new = (link)malloc(sizeof(link));
	new->diretory = (char *)malloc(sizeof(char) * (strlen(dir) + 1));
	strcpy(new->diretory, dir);

	new->next = NULL;

	while ((c = getchar()) != '/' && c != ' ') {
		new_dir[i++] = c;
	}
	new_dir[i] = '\0';

	/*se houver um espaco, quer dizer q vamos guardar o valor*/
	if (c == ' ') {
		new->abaixo = criar_folder_final(new_dir);
	} else
		/*se houver tab, criamos um folder*/
		new->abaixo = criar_folder(new_dir);

	return new;
}

/* Função auxiliar responável por alocar memória para
tudo o que é necessário para um novo nó */

link NEW_Node(char *buffer) {
	link x = (link)malloc(sizeof(struct node));
	/*reservar memória para novo nó*/
	/*reservar memória para nova string*/
	x->diretory = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));

	strcpy(x->diretory, buffer);
	x->next = NULL;
	return x;
}

char *find_func(link head, char *word) {
	link x = head;
	int indice = 0;
	char c = word[indice];
	int i = 0;
	char dir[67000] = {0};

	/*obter a proxima diretoria */
	while (c == '/') {
		c = word[++indice];
	}

	while (c != '/' && c != '\0') {
		dir[i++] = c;
		c = word[++indice];
	}

	dir[i] = '\0';

	/*caso de ser a ultima diretoria*/
	if (c == '\0') { /*ler o primerio elemento*/
		if (x->next == NULL) {
			if (!strcmp(x->diretory, dir)) {
				if (x->value != NULL) return (x->value);

				printf("no data\n");
				return "0";
			}
		}
		/*ler o resto do elemento*/
		for (; x->next != NULL; x = x->next) {
			if (!strcmp(x->diretory, dir)) {
				if (x->value != NULL) return (x->value);

				printf("no data\n");
				return "0";
			}
		}
		/*ler o ultimo do elemento*/
		if (!strcmp(x->diretory, dir)) {
			if (x->value != NULL) return (x->value);

			printf("no data\n");
			return "0";
		}
	}
	/*avancar na diretoria*/
	else {
		x = head;
		if (x->next == NULL) {
			if (!strcmp(x->diretory, dir))
				return find_func(x->abaixo, (word + indice));
		}
		for (x = head; x->next != NULL; x = x->next) {
			if (!strcmp(x->diretory, dir))
				return find_func(x->abaixo, (word + indice));
		}
		/*caso final*/
		if (!strcmp(x->diretory, dir)) return find_func(x->abaixo, (word + indice));
	}

	printf("not found\n");
	return "0";
}

int list_func(link head, char *word) {
	link x = head;
	int indice = 0;
	char c = word[indice];
	int i = 0;
	char dir[67000] = {0};

	/*eliminar as / a mais */
	while (c == '/') {
		c = word[++indice];
	}

	/*ler a diretoria*/
	while (c != '/' && c != '\0') {
		dir[i++] = c;
		c = word[++indice];
	}

	dir[i] = '\0';

	/*caso de ser a ultima diretoria*/
	if (c == '\0') { /*ler o primerio elemento*/
		if (x->abaixo != NULL) {
			x = x->abaixo;
			if (x->next == NULL) {
				printf("%s\n", x->diretory);
			}
			/*ler o resto do elemento*/
			for (; x->next != NULL; x = x->next) {
				printf("%s\n", x->diretory);
			}
			/*ler o ultimo do elemento*/

			printf("%s\n", x->diretory);

			return 0;
		}
	}
	/*avancar na diretoria*/
	else {
		x = head;
		if (x->next == NULL) {
			if (!strcmp(x->diretory, dir))
				return list_func(x->abaixo, (word + indice));
		}
		for (x = head; x->next != NULL; x = x->next) {
			if (!strcmp(x->diretory, dir))
				return list_func(x->abaixo, (word + indice));
		}
		/*caso final*/
		if (!strcmp(x->diretory, dir)) return list_func(x->abaixo, (word + indice));
	}
	return -1;
}