#include "nlist.h"

/**
 * 初始化链表
 * @param list 待初始化的链表
 */
void nlist_init(nlist_t *list)
{
    list->first = list->last = (nlist_node_t *)0;
    list->count = 0;
}