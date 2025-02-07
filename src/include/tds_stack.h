/******************************************************************************
 * File: stack.h
 * Author: Tiago Barbosa
 * Description: Implementação de uma stack (pilha) para sistemas embarcados.
 *              Esta implementação é modular e escalável, podendo ser usada
 *              em diferentes hardwares, incluindo microcontroladores como o ESP32S3.
 * Created on: 04/02/2025
 * Version: 1.0
 ******************************************************************************/

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include <stdbool.h>  // Para tipo booleano (true/false)
#include <stdint.h>   // Para tipos de dados como uint8_t, int32_t, etc.
#include <stdio.h>
#include <stdlib.h>  // Para malloc, free
#include <string.h>  // para memcpy, memove

/* Defines ------------------------------------------------------------------*/
// #define STACK_MAX_SIZE 100  // Tamanho máximo da stack (ajuste conforme necessário)

/* Typedefs -----------------------------------------------------------------*/
typedef struct tds_stack_instance_t* tds_stack_t;

/* Function Prototypes ------------------------------------------------------*/

struct tds_stack_instance_t {
    struct tds_stack_node_t* top;  // Aponta para o nó do topo da pilha
    uint32_t capacity;             // Capacidade máxima da pilha
    uint32_t elements;             // Tamanho de um único elemento (bytes)
    uint32_t size;                 // Quantidade atual de elementos na pilha
};

struct tds_stack_node_t {
    void* data;                     // Armazena o dado genérico
    struct tds_stack_node_t* next;   // Ponteiro para o próximo nó
};

tds_stack_t tds_stack_create(uint32_t capacity, size_t element_size);
bool tds_stack_push(tds_stack_t instance, const void * data);
bool tds_stack_empty(tds_stack_t instance);




#ifdef __cplusplus
}
#endif

#endif  // STACK_H