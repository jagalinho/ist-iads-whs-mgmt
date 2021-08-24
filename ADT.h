#ifndef ADT
#define ADT

#include "item.h"

#define N_SLOTS 65536	//Equivalente a 0xFFFF + 1, ou seja, a quantidade de indices diferentes que a funcao 'hash' retorna.

typedef struct node {
	Item item;
	struct node *next;
} *link;

typedef struct hashtable {
	link *heads;
	int size;
	Item max;
} *Hashtable;

Hashtable initHash();
int hash(unsigned int itemCode);
void insert(Hashtable hashtable, Item item);
Item search(Hashtable hashtable, unsigned int itemCode);
int cmpMax(Item max, Item item);
void addItem(Hashtable hashtable, Item item);
void removeItem(Hashtable hashtable, unsigned int itemCode);
Item getMax(Hashtable hashtable);
void printSorted(Hashtable hashtable);
int getSize(Hashtable hashtable);
void endHash(Hashtable hashtable);

#endif
