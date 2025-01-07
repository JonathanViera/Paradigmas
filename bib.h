#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCOS 100

// Estrutura para armazenar informações sobre os blocos
typedef struct {
    void* endereco;
    int referencias;
} Bloco;

Bloco blocos[MAX_BLOCOS];
int total_blocos = 0;

// Função para alocar memória
void* malloc2(size_t tamanho) {
    if (total_blocos >= MAX_BLOCOS) {
        printf("Erro: Limite de blocos atingido.\n");
        exit(1);
    }

    void* memoria = malloc(tamanho);
    if (memoria == NULL) {
        printf("Erro: Falha ao alocar memória.\n");
        exit(1);
    }

    blocos[total_blocos].endereco = memoria;
    blocos[total_blocos].referencias = 1;
    total_blocos++;

    return memoria;
}

// Função para encontrar o índice de um bloco
int encontra_bloco(void* endereco) {
    for (int i = 0; i < total_blocos; i++) {
        if (blocos[i].endereco == endereco) {
            return i;
        }
    }
    return -1;
}

// Função para liberar memória
void libera_bloco(int indice) {
    free(blocos[indice].endereco);
    for (int i = indice; i < total_blocos - 1; i++) {
        blocos[i] = blocos[i + 1];
    }
    total_blocos--;
}

// Função para atualizar referências
void atrib2(void** antigo, void* novo) {
    if (*antigo != NULL) {
        int indice_antigo = encontra_bloco(*antigo);
        if (indice_antigo != -1) {
            blocos[indice_antigo].referencias--; 
            if (blocos[indice_antigo].referencias == 0) {
                libera_bloco(indice_antigo);
            }
        }
    }

    if (novo != NULL) {
        int indice_novo = encontra_bloco(novo);
        if (indice_novo != -1) {
            blocos[indice_novo].referencias++;
        }
    }

    *antigo = novo;
}
void dump()
{
    printf("Estado atual da memória:\n");
    printf("Total de blocos: %d\n", total_blocos);
    for (int i = 0; i < total_blocos; i++)
    {
        printf("Bloco %d: Endereço = %p, Referências = %d\n",
               i, blocos[i].endereco, blocos[i].referencias);
    }
    printf("\n");
}

