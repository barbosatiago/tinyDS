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
    void*                        data;
    struct tds_stack_instance_t* next;
    uint32_t                     capacity;
};

tds_stack_t tds_stack_create(uint32_t capacity);
uint32_t tds_stack_capacity(tds_stack_t instance);

#ifdef __cplusplus
}
#endif

#endif  // STACK_H