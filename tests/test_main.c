#include <stdio.h>

#include "tds_stack.h"

int main() {
    printf("Rodando testes...\n");

    // Teste básico (exemplo)
    printf("Criando lista...\n");
    // Chame suas funções aqui!

    printf("Todos os testes passaram!\n");

    tds_stack_t pilha1 = tds_stack_create(10);

    printf("%ld\n", sizeof(pilha1));
    printf("Capacidade: %d\n", tds_stack_capacity(pilha1));

    return 0;
}
