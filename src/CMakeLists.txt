add_library(ds_library 
    ds_list.c
    ds_stack.c
    ds_queue.c
    ds_ringbuffer.c
    ds_hashtable.c
    ds_memory.c
)
# Adiciona os headers ao include path
target_include_directories(ds_library PUBLIC include)
