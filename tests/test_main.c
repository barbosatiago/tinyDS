#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "tds_queue.h"  // Sua API de fila

void test_queue_edge_cases() {
    printf("\n[Test] Casos extremos...\n");

    int out;
    
    // 1. Tentativa de criar uma fila com capacidade inválida
    printf("-> Criando fila com capacidade 0 (deve falhar)...\n");
    tds_queue_t queue_invalid = tds_queue_create(0, sizeof(int));
    if (!queue_invalid) {
        printf("Correto! Fila inválida não foi criada.\n");
    } else {
        printf("Erro! A API permitiu uma fila inválida.\n");
    }

    // 2. Tentando enfileirar em uma fila nula
    printf("-> Inserindo em fila NULL (deve falhar)...\n");
    if (!tds_queue_enqueue(NULL, &out)) {
        printf("Correto! Não é possível enfileirar em uma fila nula.\n");
    } else {
        printf("Erro! A API permitiu enfileirar em NULL.\n");
    }

    // 3. Tentando desenfileirar de uma fila nula
    printf("-> Removendo de fila NULL (deve falhar)...\n");
    if (!tds_queue_dequeue(NULL, &out)) {
        printf("Correto! Não é possível remover de uma fila nula.\n");
    } else {
        printf("Erro! A API permitiu remover de NULL.\n");
    }

    // 4. Criando uma fila válida
    printf("-> Criando fila válida...\n");
    tds_queue_t queue = tds_queue_create(2, sizeof(int));
    if (!queue) {
        printf("Erro: Falha ao criar a fila!\n");
        return;
    }

    // 5. Tentando enfileirar um ponteiro nulo
    printf("-> Inserindo ponteiro NULL na fila (deve falhar)...\n");
    if (!tds_queue_enqueue(queue, NULL)) {
        printf("Correto! Não é possível enfileirar NULL.\n");
    } else {
        printf("Erro! A API permitiu enfileirar NULL.\n");
    }

    // 6. Tentando desenfileirar para um ponteiro nulo
    int val = 42;
    printf("-> Inserindo 42 na fila...\n");
    tds_queue_enqueue(queue, &val);

    printf("-> Tentando remover para ponteiro NULL (deve falhar)...\n");
    if (!tds_queue_dequeue(queue, NULL)) {
        printf("Correto! Não é possível remover para NULL.\n");
    } else {
        printf("Erro! A API permitiu remover para NULL.\n");
    }

    // 7. Tentando liberar memória de uma fila nula (simulando destroy)
    printf("-> Tentando liberar fila NULL...\n");
    free(NULL);  // Deve ser seguro, mas apenas um teste

    printf("-> Liberando fila válida...\n");
    free(queue);  // Como ainda não temos um destroy, usamos free()

    printf("Testes extremos finalizados!\n");
}

int main() {
    test_queue_edge_cases();
    return 0;
}
