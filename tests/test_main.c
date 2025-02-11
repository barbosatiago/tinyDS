#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "tds_queue.h"  // Inclua seu cabeçalho da fila

#define NUM_OPERATIONS 100000

// A fila global que será usada na thread única
tds_queue_t queue;

// Função para testar enfileiramento e desenfileiramento em uma única thread
void test_single_thread_operations() {
    printf("Iniciando testes com thread única...\n");

    // Enfileirar NUM_OPERATIONS elementos
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        if (!tds_queue_enqueue(queue, &i)) {
            printf("Falhou ao enfileirar o elemento %d!\n", i);
        }
    }

    // Verificar a fila após enfileiramento
    printf("Enfileiramento concluído. Iniciando desenfileiramento...\n");

    // Desenfileirar NUM_OPERATIONS elementos
    int out;
    for (int i = 0; i < NUM_OPERATIONS; i++) {
        if (!tds_queue_dequeue(queue, &out)) {
            printf("Falhou ao desenfileirar o elemento %d!\n", i);
        } else if (out != i) {
            // Verificar se os elementos desenfileirados estão na ordem correta
            printf("Erro: Esperado %d, mas desenfileirado %d.\n", i, out);
        }
    }

    // Verificar se a fila está vazia após todas as operações
    if (!tds_queue_empty(queue)) {
        printf("Erro: A fila não está vazia após todas as operações!\n");
    }

    printf("Testes com thread única concluídos com sucesso.\n");
}

int main() {
    // Criar a fila com capacidade suficiente para armazenar todos os elementos
    queue = tds_queue_create(NUM_OPERATIONS, sizeof(int));
    if (queue == NULL) {
        printf("Falha ao criar a fila!\n");
        return 1;
    }

    // Testar a fila em um único thread
    test_single_thread_operations();

    // Destruir a fila
    if (!tds_queue_destroy(queue)) {
        printf("Erro ao destruir a fila!\n");
    } else {
        printf("Fila destruída com sucesso.\n");
    }

    return 0;
}
