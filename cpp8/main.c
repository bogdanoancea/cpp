#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    //printf("Hello world!\n");
    Queue q = Q_New();

    //insert two integers

    int* x1 = (int*) malloc(sizeof(int));
    *x1 = 5;

    int* x2 = (int*) malloc(sizeof(int));
    *x2 = 15;

    Enq(q, x1);
    Enq(q, x2);

    //extragem cele doua elemente si le afisam
    int* d1 =  Deq(q);
    printf("\n d1 = %d", *d1);

    int* d2 =  Deq(q);
    printf("\n d2 = %d", *d2);


    return 0;
}
