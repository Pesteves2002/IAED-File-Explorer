#ifndef _mergesort_H
#define _mergesort_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comandos.h"

#define exch(A, B) \
	{                \
		link t = A;    \
		A = B;         \
		B = t;         \
	}

void mergesort(link a[], int left, int right, link aux[]);
void merge(link a[], int left, int m, int right, link aux[]);

#endif