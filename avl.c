#include <stdlib.h>

#define key(A) A
#define less(A, B) (key(A) < key(B))
#define exch(A, B) \
	{                \
		Item t = A;    \
		A = B;         \
		B = t;         \
	}
#define compexch(A, B) \
	if (less(B, A)) exch(A, B)

#define eq(A, B) (A == B)

typedef int Key;

typedef struct Number {
	Key value;
} * Item;

typedef struct node {
	Item item;
	struct node *l;
	struct node *r;
} * link;

static link head;

void init() { head = NULL; }

link NEW(Item item, link l, link r) {
	link x = (link)malloc(sizeof(struct node));
	x->item = item;
	x->l = l;
	x->r = r;
	return x;
}

link search(link h, Item v) {
	if (h == NULL) return NULL;
	if (eq(v, h->item)) return h;
	if (less(v, h->item))
		return search(h->l, v);
	else
		return search(h->r, v);
}

link insert(link h, Item item) {
	Item v = item;
	if (h == NULL) return NEW(item, NULL, NULL);
	if (less(v, h->item))
		h->l = insert(h->l, item);
	else
		h->r = insert(h->r, item);
	return h;
}