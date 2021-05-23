
#include "mergesort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mergesort(link a[], int left, int right, link aux[]) {
	int m = (right + left) / 2;
	if (right <= left) return;
	mergesort(a, left, m, aux);
	mergesort(a, m + 1, right, aux);
	merge(a, left, m, right, aux);
}

void merge(link a[], int left, int m, int right, link aux[]) {
	int i, j, k;
	for (i = m + 1; i > left; i--) aux[i - 1] = a[i - 1];

	for (j = m; j < right; j++) aux[right + m - j] = a[j + 1];

	for (k = left; k <= right; k++)

		if (strcmp(aux[j]->diretory, aux[i]->diretory) < 0 || i == m + 1)
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
}