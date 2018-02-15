#include <stdio.h>
#include <stdlib.h>


void citeste(int* v, int n) {
    int i;
    for(i = 0; i < n ; i++ ) {
        printf("v[%d]=", i);
        scanf("%d", (v+i));
    }
}


void afiseaza_invers(int* v, int n) {
    if(n>0)
        afiseaza_invers(v, n-1);

    printf("v[%d]=%d", n-1, v[n-1]);
}
int main()
{
    int n,*v;
    printf("n=");
    scanf("%d", &n);

    v = (int*)malloc(sizeof(int)* n);

    citeste(v,n);

    afiseaza_invers(v,n);

    return 0;
}
