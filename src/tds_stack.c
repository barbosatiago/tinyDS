/******************************************************************************
 * File: stack.c
 * Author: Tiago Barbosa
 * Description: Implementation of a stack (LIFO) for embedded systems.
 *              This implementation is modular and scalable, suitable for different
 *              hardware platforms, including microcontrollers like the ESP32S3.
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

/**
 * @brief Creates a new stack instance.
 *
 * This function initializes a stack with the specified capacity and element size.
 * It allocates memory for the stack structure and the stack elements.
 *
 * @param capacity The maximum number of elements the stack can hold.
 * @param element_size The size of each element in bytes.
 * @return tds_stack_t A handle to the created stack instance.
 */
tds_stack_t tds_stack_create(uint32_t capacity, size_t element_size) {
    printf("[LOG] Creating stack with capacity %u and element size of %zu bytes...\n", capacity, element_size);

    tds_stack_t stack = (tds_stack_t) malloc(sizeof(struct tds_stack_instance_t));
    if (!stack) {
        printf("[ERROR] Failed to allocate memory for the stack.\n");
        return NULL;
    }

    stack->top      = NULL;
    stack->capacity = capacity;
    stack->size     = 0;
    stack->elements = element_size;

    printf("[LOG] Stack created successfully!\n");
    return stack;
}

/**
 * @brief Pushes a new element onto the stack.
 *
 * Adds a new element to the top of the stack. If the stack is full, the operation
 * fails and returns false.
 *
 * @param instance The stack instance.
 * @param data Pointer to the data to be pushed onto the stack.
 * @return true If the element was successfully pushed onto the stack.
 * @return false If the stack is full and the element cannot be added.
 */
bool tds_stack_push(tds_stack_t instance, const void *data) {
    if (!instance) {
        printf("[ERROR] Stack is not initialized!\n");
        return false;
    }
    if (instance->size >= instance->capacity) {
        printf("[ERROR] Stack is full! Maximum capacity reached (%u elements).\n", instance->capacity);
        return false;
    }

    printf("[LOG] Inserting element %u into the stack...\n", instance->size + 1);

    struct tds_stack_node_t *new_node = (struct tds_stack_node_t *) malloc(sizeof(struct tds_stack_node_t));
    if (!new_node) {
        printf("[ERROR] Failed to allocate memory for new node.\n");
        return false;
    }

    new_node->data = malloc(instance->elements);
    if (!new_node->data) {
        printf("[ERROR] Failed to allocate memory for the node data.\n");
        free(new_node);
        return false;
    }

    memcpy(new_node->data, data, instance->elements);

    new_node->next = instance->top;
    instance->top  = new_node;
    instance->size++;

    printf("[LOG] Element inserted successfully! Current stack size: %u\n", instance->size);
    return true;
}

/**
 * @brief Pops the top element from the stack.
 *
 * Removes the top element from the stack and stores its data in the provided pointer.
 *
 * @param instance The stack instance.
 * @param data Pointer where the popped element's data will be stored.
 * @return true If the element was successfully popped from the stack.
 * @return false If the stack is empty.
 */
bool tds_stack_pop(tds_stack_t instance, void *data) {
    if (!instance) {
        printf("[ERROR] Stack is not initialized!\n");
        return false;
    }

    if (instance->size == 0) {
        printf("[ERROR] Stack is empty!\n");
        return false;
    }

    struct tds_stack_node_t *node_to_remove = instance->top;  // Node to be removed

    // Copy the data from the node to the output buffer
    memcpy(data, node_to_remove->data, instance->elements);

    // Update the stack top
    instance->top = node_to_remove->next;

    // Free the memory of the removed node
    free(node_to_remove->data);
    free(node_to_remove);

    instance->size--;

    printf("[LOG] Element removed successfully! Current stack size: %u\n", instance->size);

    return true;
}

/**
 * @brief Checks if the stack is empty.
 *
 * Determines if the stack has any elements stored.
 *
 * @param instance The stack instance.
 * @return true If the stack is empty (contains no elements).
 * @return false If the stack has one or more elements.
 */
bool tds_stack_empty(tds_stack_t instance) {
    if (!instance) {
        printf("[LOG] Stack does not exist\n");
        return true;  // We consider a non-existing stack as "empty"
    }

    bool is_empty = (instance->size == 0);

    printf("The stack is %s\n", is_empty == 0 ? "not empty\n" : "empty\n");

    return is_empty;
}

/**
 * @brief Peeks at the top element of the stack without removing it.
 *
 * Retrieves the data from the top of the stack, but does not alter the stack.
 *
 * @param instance The stack instance.
 * @param data Pointer where the top element's data will be stored.
 * @return true If the top element was successfully retrieved.
 * @return false If the stack is empty.
 */
bool tds_stack_peek(tds_stack_t instance, void *data) {
    if (!instance) {
        printf("[LOG] Stack does not exist\n");
        return false;
    }

    memcpy(data, instance->top->data, instance->elements);
    return true;
}

/**
 * @brief Removes and pops the top element from the stack (internal use only).
 *
 * This function is used internally to remove the top node of the stack and
 * perform necessary clean-up. It should not be used directly by users.
 *
 * @param instance The stack instance.
 * @return true If the element was successfully removed.
 * @return false If the stack was empty.
 */
static bool tds_stack_remove_pop(tds_stack_t instance) {
    if (!instance) {
        printf("[ERROR] Stack is not initialized\n");
        return false;
    }

    if (instance->size == 0) {
        printf("[ERROR] Stack is empty\n");
        return false;
    }

    struct tds_stack_node_t *node_temp = instance->top;
    instance->top                      = node_temp->next;
    free(node_temp->data);
    free(node_temp);
    instance->size--;

    printf("[LOG] Element removed successfully! Current stack size: %u\n", instance->size);

    return true;
}

/**
 * @brief Destroys the stack and frees all allocated memory.
 *
 * This function will release memory used for the stack structure and all of its nodes.
 *
 * @param instance The stack instance.
 * @return true If the stack was successfully destroyed.
 * @return false If there was an error during the destruction process.
 */
bool tds_stack_destroy(tds_stack_t instance) {
    if (!instance) {
        printf("[ERROR] Stack not initialized");
        return false;
    }

    if (instance->size > 0) {
        while (!instance->top) {
            tds_stack_remove_pop(instance);
        }
    }

    free(instance);
    printf("[LOG] Stack destroyed successfully\n");
    return true;
}

#ifdef __cplusplus
}
#endif

#endif  // STACK_H
