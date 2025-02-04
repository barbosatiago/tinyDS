add_library(ds_library 
    tds_list.c
    tds_stack.c
    tds_queue.c
    tds_ringbuffer.c
    tds_hashtable.c
    tds_memory.c
)
# Adiciona os headers ao include path
target_include_directories(ds_library PUBLIC include)
