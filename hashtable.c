#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int M; /*size of the hashtable*/
static int N; /*number of elements in the hashtable*/

static link *st; /*hashtable*/

void STinit(int m) {
	int i;
	M = m;
	N = 0;
	st = (link *)malloc(M * sizeof(link));
	for (i = 0; i < M; i++) st[i] = NULL;
}

void STinsert(link p) {
	int i = hashU(p->value, M);
	while (st[i] != NULL) i = (i + 1) % M;
	st[i] = p;

	if (N++ > M / 2) expand();
}

link STsearch(char *v) {
	int i = hashU(v, M);
	while (st[i] != NULL)
		if (!strcmp(st[i]->value, v))
			return st[i];
		else
			i = (i + 1) % M;

	return NULL;
}

void STdelete(link p) {
	int j, i = hashU(p->value, M);
	link v;
	while (st[i] != NULL)
		if (st[i] == p)
			break;
		else
			i = (i + 1) % M;
	if (st[i] == NULL) return;
	st[i] = NULL;
	N--;
	for (j = (i + 1) % M; st[j] != NULL; j = (j + 1) % M) {
		v = st[j];
		st[j] = NULL;
		N--;
		STinsert(v);
	}
}

/*frees the whole hashtable*/
void STfree() { free(st); }

int hashU(char *v, int M) {
	long int h, a = 31415, b = 27183;

	for (h = 0; *v != '\0'; v++, a = a * b % (M - 1)) h = (a * h + *v) % M;
	return h;
}

void expand() {
	int i;
	link *t = st;
	STinit(M + M);
	for (i = 0; i < M / 2; i++)
		if (t[i] != NULL) STinsert(t[i]);
	free(t);
}