﻿#include "net_plat.h"
#include "exmsg.h"

/**
 * @brief 核心线程通信初始化
 * 
 * @return net_err_t 
 */
net_err_t exmsg_init(void)
{
    return NET_ERR_OK;
}


/**
 * @brief 核心线程功能体
 * 
 * @param arg 
 */
static void work_thread(void *arg)
{
    // 注意要加上\n。否则由于C库缓存的关系，字符串会被暂时缓存而不输出显示
    plat_printf("exmsg is running ...\n");

    while (1)
    {
        sys_sleep(1);
    }
    
}



net_err_t exmsg_start(void)
{
    //创建核心线程
    sys_thread_t thread = sys_thread_create(work_thread, (void *)0);
    if(thread == SYS_THREAD_INVALID)
    {
        return NET_ERR_SYS;
    }

    return NET_ERR_OK;
}