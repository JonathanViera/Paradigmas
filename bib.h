#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar um bloco de memória e sua contagem de referências
typedef struct MemBlock {
    void* endereco;          // Endereço do bloco de memória
    int contagem_ref;        // Contador de referências
} MemBlock;

// Lista de blocos (limite fixo para simplificação)
#define MAX_BLOCOS 100
MemBlock blocos[MAX_BLOCOS];
int total_blocos = 0;        // Número atual de blocos gerenciados

// Função para encontrar um bloco pelo endereço
int encontrar_bloco(void* endereco) {
    for (int i = 0; i < total_blocos; i++) {
        if (blocos[i].endereco == endereco) {
            return i;
        }
    }
    return -1;
}

// Função para alocar memória e registrar o bloco
void* malloc2(size_t tamanho) {
    if (total_blocos >= MAX_BLOCOS) {
        fprintf(stderr, "Erro: Limite de blocos excedido.\n");
        exit(EXIT_FAILURE);
    }

    void* endereco = malloc(tamanho);
    if (!endereco) {
        fprintf(stderr, "Erro: Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    blocos[total_blocos].endereco = endereco;
    blocos[total_blocos].contagem_ref = 1;
    total_blocos++;

    return endereco;
}

// Função para atualizar o endereço de um ponteiro e gerenciar as referências
void atrib2(void** ponteiro_antigo, void* novo_endereco) {
    if (*ponteiro_antigo != NULL) {
        int indice = encontrar_bloco(*ponteiro_antigo);
        if (indice != -1) {
            blocos[indice].contagem_ref--;
            if (blocos[indice].contagem_ref == 0) {
                free(blocos[indice].endereco); // Libera a memória
                blocos[indice] = blocos[--total_blocos]; // Remove o bloco da lista
            }
        }
    }

    if (novo_endereco != NULL) {
        int indice = encontrar_bloco(novo_endereco);
        if (indice != -1) {
            blocos[indice].contagem_ref++;
        }
    }

    *ponteiro_antigo = novo_endereco;
}

// Função para liberar toda a memória restante
void liberar_toda_memoria() {
    for (int i = 0; i < total_blocos; i++) {
        free(blocos[i].endereco);
    }
    total_blocos = 0;
}