#include <stdio.h>
#include <stdlib.h>
#include "item.h"

Item newItem() {
	Item new = (Item)malloc(sizeof(struct product));
	
	scanf("%x %d", &(new->code), &(new->stock));
	
	return new;
}

void showItem(Item item) {
	if (item != NULL)
		printf("%08x %d\n", item->code, item->stock);
}

void incrementItem(Item item, int value) {
	item->stock += value;
	
	if (item->stock < 0)
		item->stock = 0;
}

int cmpItem(const void *a, const void *b) {
	if ((*(Item*)a)->code > (*(Item*)b)->code)
		return 1;
	else
		return ((*(Item*)a)->code != (*(Item*)b)->code ? -1 : 0);
}

/* Faz-se o uso de uma 'mask' para se retornar os 2 bytes de menor peso do codigo recebido, aplicando-se um AND bit-a-bit. */
int lastValues(unsigned int code) {
	return (code & 0xFFFF);
}

unsigned int code(Item item) {
	return (item != NULL ? item->code : -1);
}

int number(Item item) {
	return (item != NULL ? item->stock : -1);
}
