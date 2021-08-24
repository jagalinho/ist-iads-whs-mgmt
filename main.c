#include <stdio.h>
#include "item.h"
#include "ADT.h"

#define TRUE 1

int main () {
	Hashtable products = initHash();
	unsigned int productCode;
	
	while (TRUE) {
		switch (getchar()) {
		    case 'a':		//Adiciona um produto.
		    	addItem(products, newItem());
		    	getchar();
		        break;
		    case 'l':		//Imprime todos os produtos por ordem alfabetica de codigos.
		    	printSorted(products);
		    	getchar();
		        break;
		    case 'm':		//Imprime o produto com maior stock.
		    	showItem(getMax(products));
				getchar();
		        break;
		    case 'r':		//Remove o produto com o codigo dado.
		    	scanf("%x", &productCode);
		    	removeItem(products, productCode);
		    	getchar();
		        break;
		    case 'x':		//Termina o programa.
		    	printf("%d\n", getSize(products));
				endHash(products);	//Liberta toda a memoria utilizada pela estrutura de dados.
		        return 0;
		    default:
		        break;
		}
    }
    
	return 0;
}
