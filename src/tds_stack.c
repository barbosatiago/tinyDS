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

tds_stack_t tds_stack_create(uint32_t capacity) {
    struct tds_stack_instance_t *new_node = (struct tds_stack_instance_t *) malloc(sizeof(struct tds_stack_instance_t));
    new_node->data                        = NULL;
    new_node->next                        = NULL;
    new_node->capacity                    = capacity;
}

uint32_t tds_stack_capacity(tds_stack_t instance) {
    if (instance != NULL) {
        return instance->capacity;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif  // STACK_H