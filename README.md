# Tiny Data Structures (TDS) Library  

**Tiny Data Structures (TDS)** is a lightweight and efficient data structure library designed specifically for **embedded systems**. The goal is to provide **fast, reliable, and memory-efficient** implementations of common data structures, ensuring smooth operation on resource-constrained environments.  

The library is written in **C**, following best practices for **low-level memory management**, **performance optimization**, and **modular design**. It supports multiple fundamental data structures that can be used in embedded applications, real-time systems, and microcontrollers.  

## Current Features  
- **Queue** – FIFO-based queue with dynamic memory allocation.  
- **Stack** – LIFO-based stack for efficient data storage.  
- **Hashtable** – Key-value store optimized for low memory usage.  
- **List** – Singly/doubly linked list for flexible data handling.  
- **Ring Buffer** – Circular buffer for efficient data streaming.  
- **Memory Management** – Custom allocation strategies for embedded systems.  

---

## TODO List  

### 🟢 **Queue (FIFO)**  
✅ Basic queue operations (`create`, `enqueue`, `dequeue`, `peek`, `size`, `empty`).  
🔲 Implement `tds_queue_destroy(instance)` – Free allocated memory.  
🔲 Implement `tds_queue_clear(instance)` – Remove all elements without deallocating memory.  
🔲 Implement `tds_queue_full(instance)` – Check if the queue is full.  
🔲 Implement `tds_queue_capacity(instance)` – Return the queue's maximum capacity.  
🔲 Implement `tds_queue_clone(instance)` – Create a deep copy of a queue.  
🔲 Implement thread-safe versions:  
   - `tds_queue_enqueue_threadsafe(instance, data)`  
   - `tds_queue_dequeue_threadsafe(instance, data)`  

### 🟠 **Stack (LIFO)**  
🔲 Implement basic stack operations (`create`, `push`, `pop`, `peek`, `size`, `empty`).  
🔲 Implement `tds_stack_destroy(instance)` – Free allocated memory.  
🔲 Implement thread-safe stack operations.  

### 🔵 **Hashtable**  
🔲 Implement hash table with open addressing or chaining.  
🔲 Support for custom hash functions.  
🔲 Implement thread-safe operations.  

### 🟣 **Linked List**  
🔲 Implement singly and doubly linked lists.  
🔲 Support `insert`, `remove`, `find`, `size` functions.  
🔲 Implement `tds_list_destroy(instance)` – Free all nodes.  

### 🟡 **Ring Buffer**  
🔲 Implement circular buffer operations.  
🔲 Support for static and dynamic allocation.  

### 🟤 **Memory Management**  
🔲 Implement custom memory allocator for embedded systems.  
🔲 Implement memory pool management.  

---

### 🔥 **Future Improvements**  
- Optimize memory usage in all data structures.  
- Add unit tests for all implementations.  
- Improve documentation with examples.  

---

## **Contributing**  
Feel free to contribute by submitting pull requests or reporting issues! 🚀  
