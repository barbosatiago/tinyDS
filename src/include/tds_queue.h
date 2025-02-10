/******************************************************************************
 * File: queue.h
 * Author: Tiago Barbosa
 * Description: Implementation of a stack (LIFO) for embedded systems.
 *              This implementation is modular and scalable, suitable for different 
 *              hardware platforms, including microcontrollers like the ESP32S3.
 * Created on: 04/02/2025
 * Version: 1.0
 ******************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

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

/* Typedefs -----------------------------------------------------------------*/
/**
 * @brief Opaque type for queue instance
 * 
 * This type is used to handle to queue instance without exposing its internals
 * 
 */
typedef struct tds_queue_instance_t* tds_queue_t;




tds_queue_t tds_queue_create(uint32_t capacity, size_t element_size);
bool tds_queue_enqueue(tds_queue_t instance, const void* data);
bool tds_queue_dequeue(tds_queue_t instance, void* data);
// bool tds_queue_empty(tds_queue_t instance);
// bool tds_queue_peek(tds_queue_t instance, void *data);
// int  tds_queue_size(tds_queue_t instance);

#ifdef __cplusplus
}
#endif

#endif  // QUEUE_H
