﻿/**
 * @brief 定长消息队列
 * 在整个协议栈中，数据包需要排队，线程之间的通信消息也需要排队，因此需要
 * 借助于消息队列实现。该消息队列长度是定长的，以避免消息数量太多耗费太多资源
 */
#include "fixq.h"
#include "nlocker.h"
#include "dbg.h"
#include "sys.h"


/**
 * @brief 初始化定长消息队列
 */
net_err_t ifxq_init(fixq_t *q, void **buf, int size, nlocker_type_t type)
{
    q->size = size;
    q->in = q->out = q->cnt = 0;
    q->buf = (void **)0;
    q->recv_sem = SYS_SEM_INVALID;
    q->send_sem = SYS_SEM_INVALID;

    // 创建锁
    net_err_t err = nlocker_init(&q->locker, type);
    if (err < 0) 
    {
        dbg_error(DBG_QUEUE, "init locker failed!");
        return err;
    }

    // 创建发送信号量
    q->send_sem = sys_sem_create(size);
    if (q->send_sem == SYS_SEM_INVALID)  
    {
        dbg_error(DBG_QUEUE, "create sem failed!");
        err = NET_ERR_SYS;
        goto init_failed;
    }

    q->recv_sem = sys_sem_create(0);
    if (q->recv_sem == SYS_SEM_INVALID) 
    {
        dbg_error(DBG_QUEUE, "create sem failed!");
        err = NET_ERR_SYS;
        goto init_failed;
    }

    q->buf = buf;
    return NET_ERR_OK;

init_failed:

    if (q->recv_sem != SYS_SEM_INVALID) 
    {
        sys_sem_free(q->recv_sem);
    }

    if (q->send_sem != SYS_SEM_INVALID) 
    {
        sys_sem_free(q->send_sem);
    }

    nlocker_destroy(&q->locker);
    return err;

}