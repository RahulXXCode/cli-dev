#ifndef _APP_CMN_MALLOC_H_
#define _APP_CMN_MALLOC_H_

#define MAX_HEAP_SIZE		0x1000U

typedef struct malloc_ctx
{
    
    int total_size;
    int rem_size;
    dll_struct free_list;
    dll_struct active_list;
} malloc_ctx_t;

typedef enum {
    MALLOC_SUCCESS = 0,
    MALLOC_FAILED = -1,
    MALLOC_NULL_POINTER = -2,
    MALLOC_OVERFLOW = -3,
    MALLOC_FREED = -4
} malloc_status;

typedef struct memory
{
    uint8_t mem;
    dll_struct dll_node;
} memory_t;
#endif

