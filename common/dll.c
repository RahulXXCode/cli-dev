#include <stdio.h>

void dll_init_head(dll_struct *head_ptr)
{
    if (head_ptr == NULL)
    {
	return NULL;
    }
    head_ptr->prev_ptr = head_ptr;
    head_ptr->next_ptr = head_ptr;
}

int dll_add(dll_struct *cur_node, dll_struct *new_node)
{
    if (cur_node == NULL || new_node == NULL)
    {
        return -1;
    }
    new_node->prev_ptr = cur_node;
    new_node->next_ptr = cur_node->next_ptr;
    if (cur_node->next_ptr != NULL)
    {
       cur_node->next_ptr->prev_ptr = new_node;
    }
    cur_node->next_ptr = new_node;
    return 0;
}

int dll_del(dll_struct *cur_node)
{
    dll_struct *prev_node = cur_node->prev_ptr;
    dll_struct *next_node = cur_node->next_ptr;

    if (prev_node == NULL && next_node == NULL)
    {
        return -1;
    }
    prev_node->next_ptr = next_node;
    next_node->prev_ptr = prev_node;
    cur_node->next_ptr = NULL;
    cur_node->prev_ptr = NULL;
    return 0;
}
