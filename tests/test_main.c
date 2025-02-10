#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "tds_stack.h"  // Certifique-se de incluir a API correta

void test_stack_integers() {
    printf("\n[Test] Criando stack de inteiros...\n");

    tds_stack_t stack = tds_stack_create(3, sizeof(int));
    if (!stack) {
        printf("Erro: Falha ao criar a stack de inteiros!\n");
        return;
    }

    int values[] = {10, 20, 30, 40};
    int out;

    // Testando push normal
    printf("-> Inserindo 10...\n");
    tds_stack_push(stack, &values[0]);

    printf("-> Inserindo 20...\n");
    tds_stack_push(stack, &values[1]);

    printf("-> Inserindo 30...\n");
    tds_stack_push(stack, &values[2]);

    // Testando overflow
    printf("-> Tentando inserir 40 (deve falhar)...\n");
    if (!tds_stack_push(stack, &values[3])) {
        printf("Correto! Stack está cheia.\n");
    }

    // Testando peek
    if (tds_stack_peek(stack, &out)) {
        printf("Peek: Topo da pilha = %d\n", out);
    }

    // Testando pop
    printf("-> Removendo topo...\n");
    tds_stack_pop(stack, &out);
    printf("Popped: %d\n", out);

    printf("-> Removendo topo novamente...\n");
    tds_stack_pop(stack, &out);
    printf("Popped: %d\n", out);

    printf("-> Removendo topo novamente...\n");
    tds_stack_pop(stack, &out);
    printf("Popped: %d\n", out);

    // Testando underflow
    printf("-> Tentando remover de pilha vazia (deve falhar)...\n");
    if (!tds_stack_pop(stack, &out)) {
        printf("Correto! Stack está vazia.\n");
    }

    // Testando destruição
    printf("-> Destruindo stack...\n");
    if (!tds_stack_destroy(stack)) {
        printf("Erro ao destruir stack!\n");
    } else {
        printf("Stack destruída com sucesso!\n");
    }
}

void test_stack_structs() {
    printf("\n[Test] Criando stack de structs...\n");

    typedef struct {
        char nome[20];
        int idade;
    } Pessoa;

    tds_stack_t stack = tds_stack_create(2, sizeof(Pessoa));
    if (!stack) {
        printf("Erro: Falha ao criar a stack de structs!\n");
        return;
    }

    Pessoa p1 = {"Alice", 25}, p2 = {"Bob", 30}, out;

    printf("-> Inserindo Alice...\n");
    tds_stack_push(stack, &p1);

    printf("-> Inserindo Bob...\n");
    tds_stack_push(stack, &p2);

    // Testando peek
    if (tds_stack_peek(stack, &out)) {
        printf("Peek: Topo da pilha = %s, %d\n", out.nome, out.idade);
    }

    // Testando pop
    tds_stack_pop(stack, &out);
    printf("Popped: %s, %d\n", out.nome, out.idade);

    tds_stack_pop(stack, &out);
    printf("Popped: %s, %d\n", out.nome, out.idade);

    // Testando destruição
    printf("-> Destruindo stack...\n");
    if (!tds_stack_destroy(stack)) {
        printf("Erro ao destruir stack!\n");
    } else {
        printf("Stack destruída com sucesso!\n");
    }
}


int main() {
    
    test_stack_integers();
    test_stack_structs();
    return 0;
}
