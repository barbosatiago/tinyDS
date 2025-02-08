/******************************************************************************
 * File: stack.h
 * Author: Tiago Barbosa
 * Description: Implementation of a stack (LIFO) for embedded systems.
 *              This implementation is modular and scalable, suitable for different 
 *              hardware platforms, including microcontrollers like the ESP32S3.
 * Created on: 04/02/2025
 * Version: 1.0
 ******************************************************************************/

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include <stdbool.h>  // For boolean type (true/false)
#include <stdint.h>   // For data types like uint8_t, int32_t, etc.
#include <stdio.h>
#include <stdlib.h>  // For malloc, free
#include <string.h>  // For memcpy, memmove

/* Defines ------------------------------------------------------------------*/
// #define STACK_MAX_SIZE 100  // Maximum size of the stack (adjust as necessary)

/* Typedefs -----------------------------------------------------------------*/
/**
 * @brief Opaque type for stack instance.
 * 
 * This type is used to handle the stack instance without exposing its internals.
 */
typedef struct tds_stack_instance_t* tds_stack_t;

/* Function Prototypes ------------------------------------------------------*/

/**
 * @brief Structure representing a stack instance.
 * 
 * This structure holds the stack's state, including its capacity, current size,
 * and the pointer to the top of the stack (which is a linked list node).
 */
struct tds_stack_instance_t {
    struct tds_stack_node_t* top;       /**< Points to the top node of the stack */
    uint32_t                 capacity;  /**< Maximum capacity of the stack */
    uint32_t                 elements;  /**< Size of a single element in bytes */
    uint32_t                 size;      /**< Current number of elements in the stack */
};

/**
 * @brief Structure representing a node in the stack.
 * 
 * Each node contains a pointer to the stored data and a pointer to the next node.
 */
struct tds_stack_node_t {
    void*                    data;  /**< Stores the generic data */
    struct tds_stack_node_t* next;  /**< Pointer to the next node in the stack */
};

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
tds_stack_t tds_stack_create(uint32_t capacity, size_t element_size);

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
bool tds_stack_push(tds_stack_t instance, const void* data);

/**
 * @brief Checks if the stack is empty.
 * 
 * Determines if the stack has any elements stored. 
 * 
 * @param instance The stack instance.
 * @return true If the stack is empty (contains no elements).
 * @return false If the stack has one or more elements.
 */
bool tds_stack_empty(tds_stack_t instance);

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
bool tds_stack_peek(tds_stack_t instance, void* data);

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
bool tds_stack_pop(tds_stack_t instance, void* data);

/**
 * @brief Destroys the stack and frees all allocated memory.
 * 
 * This function will release memory used for the stack structure and all of its nodes.
 * 
 * @param instance The stack instance.
 * @return true If the stack was successfully destroyed.
 * @return false If there was an error during the destruction process.
 */
bool tds_stack_destroy(tds_stack_t instance);

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
static bool tds_stack_remove_pop(tds_stack_t instance);

#ifdef __cplusplus
}
#endif

#endif  // STACK_H
