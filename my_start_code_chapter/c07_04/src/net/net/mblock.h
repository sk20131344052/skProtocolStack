#ifndef MBLOCK_H
#define MBLOCK_H

#include "nlist.h"
#include "nlocker.h"


/**
 * @brief 存储管块管理器
 */
typedef struct _mblock_t
{
    void *start;       // 所有存储的起始地址
    nlist_t free_list; // 空闲的消息队列
    nlocker_t locker;  // 访问的锁
    sys_sem_t alloc_sem; // 分配同步用信号量
    
}mblock_t;

net_err_t mblock_init (mblock_t* mblock, void * mem, int blk_size, int cnt, nlocker_type_t share_type);

void *mblock_alloc(mblock_t *block, int ms);
int mblock_free_cnt(mblock_t *list);

#endif