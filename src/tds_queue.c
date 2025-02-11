/******************************************************************************
 * File: queue.c
 * Author: Tiago Barbosa
 * Description: Implementation of a stack (LIFO) for embedded systems.
 *              This implementation is modular and scalable, suitable for different
 *              hardware platforms, including microcontrollers like the ESP32S3.
 * Created on: 04/02/2025
 * Version: 1.0
 ******************************************************************************/

#ifndef QUEUE_C
#define QUEUE_C

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include "tds_queue.h"

/* Defines ------------------------------------------------------------------*/

/* Typedefs -----------------------------------------------------------------*/

/* Function Prototypes ------------------------------------------------------*/

struct tds_queue_instance_t {
    struct tds_queue_node_t* head;
    struct tds_queue_node_t* tail;
    uint32_t                 capacity;
    uint32_t                 elements;
    uint32_t                 size;
};

struct tds_queue_node_t {
    void*                    data;
    struct tds_queue_node_t* next;
};

tds_queue_t tds_queue_create(uint32_t capacity, size_t element_size) {
    if (capacity == 0 || element_size == 0) {
        // printf("[LOG] Capacity is invalid!\n");
        return NULL;
    }

    // printf("[LOG] Creating queue with capacity %u and element size of %zu bytes...\n", capacity, element_size);
    tds_queue_t new_queue = (tds_queue_t) malloc(sizeof(struct tds_queue_instance_t));

    if (!new_queue) {
        // printf("[ERROR] Failed to allocate memory for the queue.\n");
        return NULL;
    }

    new_queue->head     = NULL;
    new_queue->tail     = NULL;
    new_queue->elements = element_size;
    new_queue->capacity = capacity;
    new_queue->size     = 0;

    // printf("[LOG] Queue create sucessfully\n");
    return new_queue;
}

bool tds_queue_enqueue(tds_queue_t instance, const void* data) {
    if (!instance) {
        // printf("[ERROR] Queue is not initialized!\n");
        return false;
    }

    if (instance->size >= instance->capacity) {
        // printf("[ERROR] Queue is full! Maximum capacity reached (%u elements).\n", instance->capacity);
        return false;
    }

    if (!data) {
        // printf("[ERROR] Data pointer is NULL!\n");
        return false;
    }

    instance->size += 1;
    // printf("[LOG] Inserting element %u into the queue...\n", instance->size);

    struct tds_queue_node_t* new_node = (struct tds_queue_node_t*) malloc(sizeof(struct tds_queue_node_t));
    if (!new_node) {
        // printf("[ERROR] Failed to allocate memory for new node.\n");
        return false;
    }

    new_node->data = malloc(instance->elements);
    new_node->next = NULL;
    if (!new_node->data) {
        // printf("[ERROR] Failed to allocate memory for the node data.\n");
        free(new_node);
        return false;
    }
    memcpy(new_node->data, data, instance->elements);

    if (!instance->head) {
        instance->head = new_node;
        instance->tail = new_node;
    } else {
        instance->tail->next = new_node;
        instance->tail       = new_node;
    }

    // printf("[LOG] Element inserted sucessfully! Current queue size: %u\n", instance->size);
    return true;
}

bool tds_queue_dequeue(tds_queue_t instance, void* data) {
    if (!instance) {
        // printf("[ERROR] Queue is not initialized!\n");
        return false;
    }

    if (!data) {
        // printf("[ERROR] Data pointer is NULL!\n");
        return false;
    }

    if (instance->size == 0) {
        // printf("[ERROR] Queue is empty!\n");
        return false;
    }

    struct tds_queue_node_t* temp = instance->head;
    memcpy(data, temp->data, instance->elements);

    instance->head = instance->head->next;

    if (!instance->head) {
        instance->tail = NULL;
    }

    free(temp->data);
    free(temp);

    instance->size--;

    // printf("[LOG] Element removed sucessfully! Current queue stack size: %u\n", instance->size);

    return true;
}

bool tds_queue_empty(tds_queue_t instance) {
    if (!instance) {
        // printf("[ERROR] Queue is not initialized!\n");
        return true;
    }

    bool empty = (instance->size == 0);

    return (!empty) ? false : true;
}

bool tds_queue_peek(tds_queue_t instance, void* data) {
    if (!instance) {
        // printf("[ERROR] Queue is not initialized!\n");
        return false;
    }

    if (!data) {
        // printf("[ERROR] Data pointer is invalid!\n");
        return false;
    }

    memcpy(data, instance->head->data, instance->elements);
    return true;
}

int tds_queue_size(tds_queue_t instance) {
    if (!instance) {
        // printf("[ERROR] Queue is not initialized!\n");
        return -1;
    }

    return instance->size;
}

bool tds_queue_destroy(tds_queue_t instance) {
    if (!instance) {
        return true;
    }

    if (instance->size > 0) {
        while (!instance->head) {
            struct tds_queue_node_t* temp = instance->head;
            instance->head                = instance->head->next;
            if (!instance->head) {
                instance->tail = NULL;
            }
            free(temp->data);
            free(temp);

            instance->size--;
        }
    }

    free(instance);

    return true;
}

#ifdef __cplusplus
}
#endif

#endif  // QUEUE_H
