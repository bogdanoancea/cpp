#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#pragma warning (disable:4996)

void insert(Queue Q) {
	int* x = (int*)malloc(sizeof(int));
	printf("Dati valorea pe care doriti sa o introduceti:");
	scanf("%d", x);
	Enq(Q, x);
}

void remove1(Queue Q) {
	int *x;
	x = Deq(Q);
	printf("Elementul sters din coada este: %d \n", *x);
}

main() {
	int optiune = 0;
	Queue Q = Q_New();
	while (optiune != 4) {
		printf("1. Inserati un element in coada. \n");
		printf("2. Inlaturati un element din coada. \n");
		printf("3. Afisati toate elementele cozii. \n");
		printf("4. Parasiti programul. \n");
		printf("Introduceti optiunea dorita:");
		scanf("%d", &optiune);
		if (optiune == 1)
			insert(Q);
		else if (optiune == 2)
			remove1(Q);
		else if (optiune == 3)
			display(Q);
		else if (optiune == 4)
			break;
	}
}