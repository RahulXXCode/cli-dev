#include <stdio.h>

/*
 * This file mainly is used to create a custom malloc based on linked list allocation!
 * This will be a faster way for the app to dynamically allocate memory instead of using
 * standard malloc function as the memory is already allocated at the start
 * of the APP.
 */

#define MAX_HEAP_SIZE               0x1000U
#define APP_MALLOC(size)       mempool_get(size)

int app_custom_malloc(void* ptr, int size);
static memory_t buffer[APP_MAX_HEAP_SIZE];
static malloc_t malloc_ctx;


/*
 * Get current linked list node(which will be the last one that
 * is allocated) and check requested size < remaining size then
 * add nodes. now get the node pointing to respecitve array
 * based on size!
 *
 * So this is like we need to maintain free node which 
 * corresponds to memory array and get a dll node from the free
 * list?
 *
 */
void* mempool_get(int size)
{
    void* ptr = NULL;
    if (size > MAX_HEAP_SIZE)
    {
        return APP_MALLOC_FAILED;
    }
    else
    {
        /*
	 * As of now, the requested size if less than heap size! now get the linked list end ptr!
	 *
	 */
	 dll_get_node();
    }
}

void mempool_init()
{
    if (dll_init_head())
    {
        printf("\n dll init failed in %s", __FUNCTION__);
    }
}
