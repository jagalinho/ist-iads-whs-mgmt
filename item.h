#ifndef ITEM
#define ITEM

typedef struct product {
	unsigned int code;
	int stock;
} *Item;

//Na estrutura acima o codigo do produto e definido como 'unsigned int' pois para a comparacao de codigos e necessario que os seus valores em decimal sejam todos positivos, o que nao aconteceria caso fosse definido como 'int', porque, como sao utilizados todos os 32 bits, e possivel que o bit de maior peso seja 1, o que tornaria o numero negativo em decimal.

Item newItem();
void showItem(Item item);
void incrementItem(Item item, int value);
int cmpItem(const void *a, const void *b);
int lastValues(unsigned int code);
unsigned int code(Item item);
int number(Item item);

#endif
