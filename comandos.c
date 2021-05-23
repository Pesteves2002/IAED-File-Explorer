
#include "comandos.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "mergesort.h"

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

void set_func(link *order) {
	char path[6000] = {0};
	*order = insertEnd(*order, path);
}

link insertEnd(link head, char path[]) {
	link x = head;
	char dir[67000];
	char c = getchar();
	int i = 0;

	while (c == '/') {
		c = getchar();
	}

	/*obter a proxima diretoria */
	while (c != '/' && c != ' ') {
		dir[i++] = c;
		c = getchar();
	}
	dir[i++] = '\0';

	/*caso de ser vazia*/
	if (head == NULL) {
		if (c == ' ') {
			return criar_folder_final(dir, path);
		}
		/*se houver tab, criamos um folder*/
		return criar_folder(dir, path);
	}

	/*condicao para mudar um valor*/
	if (c == ' ') {
		char troca[67000];
		int i = 0;
		link aux = head;

		for (; aux != NULL; aux = aux->next) {
			if (!strcmp(dir, aux->diretory)) {
				while ((c = getchar()) != '\n' && c != EOF) troca[i++] = c;

				troca[i++] = '\0';
				if (aux->value != NULL) STdelete(aux);
				free(aux->value);
				aux->value = (char *)malloc(sizeof(char) * i);
				strcpy(aux->value, troca);

				STinsert(aux);
				return head;
			}
		}
	}

	/*verificar quando chega ao fim da lista*/
	for (; x->next != NULL; x = x->next) {
		/*se forem iguais chama para a mesma diretoria */
		if (!strcmp(dir, x->diretory)) {
			strcat(path, "/");
			strcat(path, dir);
			x->abaixo = insertEnd(x->abaixo, path);
			return head;
		}
	}
	if (!strcmp(dir, x->diretory)) {
		strcat(path, "/");
		strcat(path, dir);
		x->abaixo = insertEnd(x->abaixo, path);
		return head;
	}

	if (c == ' ') x->next = criar_folder_final(dir, path);
	/*se houver tab, criamos um folder*/
	else
		x->next = criar_folder(dir, path);

	return head;
}

link criar_folder_final(char *dir, char path[]) {
	char c;
	char valor[67000];
	int i = 0;
	link new = (link)malloc(sizeof(Node));

	new->diretory = (char *)malloc(sizeof(char) * (strlen(dir) + 1));
	strcpy(new->diretory, dir);

	while ((c = getchar()) != '\n' && c != EOF) {
		valor[i++] = c;
	}
	valor[i++] = '\0';

	new->value = (char *)malloc(sizeof(char) * i);
	strcpy(new->value, valor);

	new->fullpath = (char *)malloc(sizeof(char) * (strlen(path) + 1));
	strcpy(new->fullpath, path);

	new->abaixo = NULL;
	new->next = NULL;

	STinsert(new);

	return new;
}

link criar_folder(char *dir, char path[]) {
	char c = getchar();
	char new_dir[67000];
	int i = 0;

	link new = (link)malloc(sizeof(Node));
	new->diretory = (char *)malloc(sizeof(char) * (strlen(dir) + 1));
	strcpy(new->diretory, dir);

	new->fullpath = (char *)malloc(sizeof(char) * (strlen(path) + 1));
	strcpy(new->fullpath, path);

	new->next = NULL;
	new->abaixo = NULL;
	new->value = NULL;

	while (c == '/') {
		c = getchar();
	}

	while (c != '/' && c != ' ') {
		new_dir[i++] = c;
		c = getchar();
	}
	new_dir[i++] = '\0';
	/*se houver um espaco, quer dizer q vamos guardar o valor*/
	if (c == ' ' && strcmp("", new_dir)) {
		link final = (link)malloc(sizeof(Node));
		char valor[2000];
		int j = 0;

		while ((c = getchar()) != '\n' && c != EOF) {
			valor[j++] = c;
		}
		valor[j++] = '\0';

		final->diretory = (char *)malloc(sizeof(char) * i);
		strcpy(final->diretory, new_dir);

		final->value = (char *)malloc(sizeof(char) * j);
		strcpy(final->value, valor);

		final->abaixo = NULL;
		final->next = NULL;

		strcat(path, "/");
		strcat(path, dir);

		final->fullpath = (char *)malloc(sizeof(char) * (strlen(path) + 1));
		strcpy(final->fullpath, path);
		STinsert(final);

		new->abaixo = final;
		return new;
	}

	/*adicionar ao new*/
	if (c == ' ') {
		char valor[2000];
		int i = 0;

		while ((c = getchar()) != '\n' && c != EOF) {
			valor[i++] = c;
		}
		valor[i++] = '\0';

		new->value = (char *)malloc(sizeof(char) * i);
		strcpy(new->value, valor);

		new->abaixo = NULL;
		new->next = NULL;
		STinsert(new);
		return new;
	}

	else {
		strcat(path, "/");
		strcat(path, dir);

		/*se houver tab, criamos um folder*/
		new->abaixo = criar_folder(new_dir, path);
	}

	return new;
}

void print(link head) {
	if (!head) return;
	{
		if (head->value != NULL) {
			printf("%s/%s %s\n", head->fullpath, head->diretory, head->value);
		}
		print(head->abaixo);
		print(head->next);
	}
}

char *find_func(link head, char *word) {
	link x = head;
	int indice = 0;
	char c = word[indice];
	int i = 0;
	char dir[67000];

	/*remove the initial '/' */
	while (c == '/') {
		c = word[++indice];
	}
	/*get the directory*/
	while (c != '/' && c != '\0') {
		dir[i++] = c;
		c = word[++indice];
	}

	dir[i] = '\0';

	/*if it is the last directory*/
	if (c == '\0') {
		if (head == NULL) {
			printf(NOT_FOUND);
			return "0";
		}

		/*read the first directory*/
		if (x->next == NULL) {
			if (!strcmp(x->diretory, dir)) {
				if (x->value != NULL) return (x->value);

				printf(NO_DATA);
				return "0";
			}
		}
		/*read the rest of the directories*/
		for (; x->next != NULL; x = x->next) {
			if (!strcmp(x->diretory, dir)) {
				if (x->value != NULL) return (x->value);

				printf(NO_DATA);
				return "0";
			}
		}
		/*read the last directory*/
		if (!strcmp(x->diretory, dir)) {
			if (x->value != NULL) return (x->value);

			printf(NO_DATA);
			return "0";
		}
	}
	/*search the directory*/
	else {
		x = head;
		if (head == NULL) {
			printf(NOT_FOUND);
			return "0";
		}
		if (x->next == NULL) {
			if (!strcmp(x->diretory, dir))
				return find_func(x->abaixo, (word + indice));
		}
		for (x = head; x->next != NULL; x = x->next) {
			if (!strcmp(x->diretory, dir))
				return find_func(x->abaixo, (word + indice));
		}
		if (!strcmp(x->diretory, dir)) {
			return find_func(x->abaixo, (word + indice));
		}
	}
	printf(NOT_FOUND);
	return "0";
}

int list_func(link head, char *word) {
	link x;
	int indice = 0;
	char c = word[indice];
	int i = 0;
	char dir[67000];

	/*remove the initial '/' */
	while (c == '/') {
		c = word[++indice];
	}

	/*read the directory*/
	while (c != '/' && c != '\0') {
		dir[i++] = c;
		c = word[++indice];
	}

	dir[i] = '\0';

	/*if it is the last directory*/
	if (c == '\0') {
		if (head == NULL) return -1;

		/*find the directory*/
		else {
			link aux = head;
			for (; aux != NULL; aux = aux->next)
				if (!strcmp(dir, aux->diretory)) {
					link alfa[1000];
					link aux2[1000];
					int i = 0;
					int l;

					if (aux->abaixo == NULL) {
						return 0;
					}

					x = aux->abaixo;
					/*if there's only 1 value*/
					if (x->next == NULL) {
						printf("%s\n", x->diretory);
						return 0;
					}

					/*acumulates the various directories*/
					for (; x->next != NULL; x = x->next) {
						alfa[i++] = x;
					}
					alfa[i] = x;

					mergesort(alfa, 0, i, aux2);

					for (l = 0; l <= i; l++) printf("%s\n", alfa[l]->diretory);

					return 0;
				}
			return -1;
		}
	}
	/*check in the next directory*/
	else {
		x = head;
		if (head == NULL) return -1;

		if (x->next == NULL) {
			if (!strcmp(x->diretory, dir))
				return list_func(x->abaixo, (word + indice));
		}
		for (x = head; x->next != NULL; x = x->next) {
			if (!strcmp(x->diretory, dir))
				return list_func(x->abaixo, (word + indice));
		}
		if (!strcmp(x->diretory, dir)) {
			return list_func(x->abaixo, (word + indice));
		}
	}
	return -1;
}

link delete_func(link head, char *path) {
	link x;
	int indice = 0;
	char c = path[indice];
	int i = 0;
	char dir[67000];

	/*remove the initial '/' */
	while (c == '/') {
		c = path[++indice];
	}

	/*read the directory*/
	while (c != '/' && c != '\0') {
		dir[i++] = c;
		c = path[++indice];
	}

	dir[i] = '\0';

	/*case it is the last directory*/
	if (c == '\0') {
		link x = head;
		link aux = head;
		if (head == NULL) {
			printf(NOT_FOUND);
			return head;
		}
		/*free the first directory */
		if (!strcmp(x->diretory, dir)) {
			if (x->next != NULL)
				aux = x->next;
			else
				aux = NULL;
			free(x->diretory);
			free(x->fullpath);

			if (x->abaixo != NULL) aux_delete(x->abaixo);
			if (x->value != NULL) {
				STdelete(x);
				free(x->value);
			}
			free(x);
			return aux;
		}

		for (; x != NULL; x = x->next) {
			if (!strcmp(x->diretory, dir)) {
				aux->next = x->next;
				aux_delete(x->abaixo);
				if (x->value != NULL) {
					STdelete(x);
					free(x->value);
				}
				free(x->fullpath);
				free(x->diretory);
				free(x);
				return head;
			}
			aux = x;
		}
		printf(NOT_FOUND);
	}
	/*goes to the next diretory*/
	else {
		if (head == NULL) {
			printf(NOT_FOUND);
			return head;
		}
		x = head;
		if (x->next == NULL) {
			if (!strcmp(x->diretory, dir))
				x->abaixo = delete_func(x->abaixo, (path + indice));
			else
				printf(NOT_FOUND);
		} else {
			for (x = head; x->next != NULL; x = x->next) {
				if (!strcmp(x->diretory, dir)) {
					x->abaixo = delete_func(x->abaixo, (path + indice));
					return head;
				}
			}
			if (!strcmp(x->diretory, dir)) {
				x->abaixo = delete_func(x->abaixo, (path + indice));
				return head;
			} else {
				printf(NOT_FOUND);
			}
		}
	}
	return head;
}

void apagar(link *order) { *order = aux_delete(*order); }

link aux_delete(link head) {
	if (head == NULL) return head;

	if (head->next != NULL) {
		aux_delete(head->next);
	}
	if (head->abaixo != NULL) {
		aux_delete(head->abaixo);
	}
	/*remove from the hashtable*/
	if (head->value != NULL) STdelete(head);

	free(head->fullpath);
	free(head->diretory);
	free(head->value);
	free(head);
	return NULL;
}
