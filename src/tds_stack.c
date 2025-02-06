/******************************************************************************
 * File: stack.c
 * Author: Tiago Barbosa
 * Description: Implementação de uma stack (pilha) para sistemas embarcados.
 *              Esta implementação é modular e escalável, podendo ser usada
 *              em diferentes hardwares, incluindo microcontroladores como o ESP32S3.
 * Created on: 04/02/2025
 * Version:
 ******************************************************************************/

#ifndef STACK_C
#define STACK_C

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include "tds_stack.h"

tds_stack_t tds_stack_create(uint32_t capacity, size_t element_size) {
    printf("[LOG] Criando pilha com capacidade %u e tamanho de elemento %zu bytes...\n", capacity, element_size);
    
    tds_stack_t stack = (tds_stack_t) malloc(sizeof(struct tds_stack_instance_t));
    if (!stack) {
        printf("[ERRO] Falha ao alocar memória para a pilha.\n");
        return NULL;
    }

    stack->top = NULL;
    stack->capacity = capacity;
    stack->size = 0;
    stack->elements = element_size;

    printf("[LOG] Pilha criada com sucesso!\n");
    return stack;
}

bool tds_stack_push(tds_stack_t instance, const void *data) {
    if (!instance) {
        printf("[ERRO] Pilha não inicializada!\n");
        return false;
    }
    if (instance->size >= instance->capacity) {
        printf("[ERRO] Pilha cheia! Capacidade máxima atingida (%u elementos).\n", instance->capacity);
        return false;
    }

    printf("[LOG] Inserindo elemento %u na pilha...\n", instance->size + 1);

    struct tds_stack_node_t *new_node = (struct tds_stack_node_t *) malloc(sizeof(struct tds_stack_node_t));
    if (!new_node) {
        printf("[ERRO] Falha ao alocar memória para novo nó.\n");
        return false;
    }

    new_node->data = malloc(instance->elements);
    if (!new_node->data) {
        printf("[ERRO] Falha ao alocar memória para o dado do nó.\n");
        free(new_node);
        return false;
    }

    memcpy(new_node->data, data, instance->elements);
    
    new_node->next = instance->top;
    instance->top = new_node;
    instance->size++;

    printf("[LOG] Elemento inserido com sucesso! Tamanho atual da pilha: %u\n", instance->size);
    return true;
}

bool tds_stack_pop(tds_stack_t instance, void * data) {
    if (!instance) {
        printf("[ERRO] Pilha não inicializada!\n");
        return false;
    }

    if (instance->size == 0) {
        printf("[ERRO] Pilha está vazia!\n");
        return false;
    }

    struct tds_stack_node_t *node_to_remove = instance->top;  // Nó que será removido

    // Copia os dados do nó para o buffer de saída
    memcpy(data, node_to_remove->data, instance->elements);

    // Atualiza o topo da pilha
    instance->top = node_to_remove->next;
    
    // Libera a memória do nó removido
    free(node_to_remove->data);
    free(node_to_remove);

    instance->size--;

    printf("[LOG] Elemento removido com sucesso! Tamanho atual da pilha: %u\n", instance->size);
    
    return true;
}



#ifdef __cplusplus
}
#endif

#endif  // STACK_H