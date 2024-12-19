#include "bib.h"

int main() {
    int* a = (int*)malloc2(sizeof(int));
    *a = 10;

    int* b = NULL;
    atrib2((void**)&b, a);  // b aponta para a

    printf("Valor de a: %d\n", *a);
    printf("Valor de b: %d\n", *b);

    atrib2((void**)&b, NULL); // Remove referência de b
    atrib2((void**)&a, NULL); // Remove referência de a

    liberar_toda_memoria(); // Libera qualquer memória restante

    return 0;
}
