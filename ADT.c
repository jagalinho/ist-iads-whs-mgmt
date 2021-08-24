#include <stdio.h>
#include <stdlib.h>
#include "ADT.h"

Hashtable initHash() {
	int i;
	Hashtable hashtable = (Hashtable)malloc(sizeof(struct hashtable));
	
	hashtable->heads = (link*)malloc(N_SLOTS*sizeof(link));
	hashtable->size = 0;
	hashtable->max = NULL;
	
	for (i=0; i<N_SLOTS; i++)
		hashtable->heads[i] = NULL;
	
	return hashtable;
}

int hash(unsigned int itemCode) {
	return lastValues(itemCode);
}

void insert(Hashtable hashtable, Item item) {
	int slot = hash(code(item));
	link new = (link)malloc(sizeof(struct node));
	
	new->item = item;
	new->next = hashtable->heads[slot];
	hashtable->heads[slot] = new;
	
	hashtable->size++;
}

Item search(Hashtable hashtable, unsigned int itemCode) {
	int slot = hash(itemCode);
	link t;
	
	for (t=hashtable->heads[slot]; t!=NULL; t=t->next)
		if (code(t->item) == itemCode)
			return t->item;
	
	return NULL;
}

/* Dado um Item 'max' (que corresponde ao maximo atual) e um Item 'item', a funcao 'cmpMax' verifica se o 'item' passa a ser o novo maximo. */
int cmpMax(Item max, Item item) {
	return (number(item) > number(max) || (number(item) == number(max) && code(item) < code(max)));
}

void addItem(Hashtable hashtable, Item item) {
	Item found = search(hashtable, code(item));
	
	if (found != NULL) {
		//Nos casos em que ja nao se pode ter a certeza que o maximo corresponde ao maximo real, reinicializa-se o maximo a 'NULL' para que, tanto nao haja mais tentativas de update do mesmo, como para indicar que este tem de ser recalculado na proxima chamada a funcao 'getMax'.
		if (code(hashtable->max) == code(found) && number(item) < 0)
			hashtable->max = NULL;
		incrementItem(found, number(item));
		free(item);
		if (hashtable->max != NULL && cmpMax(hashtable->max, found))
			hashtable->max = found;
	} else {
		insert(hashtable, item);
		if (hashtable->max != NULL && cmpMax(hashtable->max, item))
			hashtable->max = item;
	}
}

void removeItem(Hashtable hashtable, unsigned int itemCode) {
	int slot = hash(itemCode);
	link prev = NULL, curr = hashtable->heads[slot];
	
	if (code(hashtable->max) == itemCode)
		hashtable->max = NULL;
	
	while (curr != NULL && code(curr->item) != itemCode) {
		prev = curr;
		curr = curr->next;
	}
	
	if (curr != NULL) {
		if (prev != NULL)
			prev->next = curr->next;
		else
			hashtable->heads[slot] = curr->next;
		free(curr->item);
		free(curr);
		hashtable->size--;
	}
}

Item getMax(Hashtable hashtable) {
	if (hashtable->max == NULL) {
		int i;
		link t;
		
		for (i=0; i!=N_SLOTS ; i++)
			for (t=hashtable->heads[i]; t!=NULL; t=t->next)
				if (cmpMax(hashtable->max, t->item))
					hashtable->max = t->item;
	}
	
	return hashtable->max;
}

void printSorted(Hashtable hashtable) {
	int i, j = 0;
	link t;
	Item *items = (Item*)malloc((hashtable->size)*sizeof(Item));
	
	for (i=0; i!=N_SLOTS ; i++)
		for (t=hashtable->heads[i]; t!=NULL; t=t->next)
			items[j++] = t->item;
	
	qsort(items, hashtable->size, sizeof(Item), cmpItem);
	
	for (i=0; i<hashtable->size; i++)
		showItem(items[i]);
	
	free(items);
}

int getSize(Hashtable hashtable) {
	return hashtable->size;
}

//A funcao 'endHash' liberta toda a memoria utilizada pela hashtable, de forma a nao existir qualquer tipo de 'memory leak'.
void endHash(Hashtable hashtable) {
	int i;
	link t, u;
	
	for (i=0; i!=N_SLOTS ; i++) {
		t = hashtable->heads[i];
		while (t != NULL) {
			u = t->next;
			free(t->item);
			free(t);
			t = u;
		}
	}
	
	free(hashtable->heads);
	free(hashtable);
}
