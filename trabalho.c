#include "bib.h"

int main()
{
    int *a = (int *)malloc2(sizeof(int));
    int *b = (int *)malloc2(sizeof(int));

    *a = 10;
    *b = 20;
   
    printf("Antes: a = %d, b = %d \n", *a, *b);
    dump();

    atrib2((void **)&b, a);// b agora aponta para o mesmo bloco que a
    atrib2((void**)&c, a);
    printf("Depois: a = %d, b = %d\n", *a, *b);
    dump();

    atrib2((void **)&a, NULL); // Libera o bloco de a
    atrib2((void **)&b, NULL);
     // Libera o bloco de b

    dump();

    return 0;
}
