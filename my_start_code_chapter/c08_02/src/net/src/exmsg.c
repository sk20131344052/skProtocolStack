#include "net_plat.h"
#include "exmsg.h"
#include "fixq.h"
#include "mblock.h"
#include "dbg.h"
#include "nlocker.h"


static void *msg_tbl[EXMSG_MSG_CNT];  //消息缓冲区
static fixq_t msg_queue;              //消息队列
static exmsg_t msg_buffer[EXMSG_MSG_CNT];   // 消息块
static mblock_t msg_block;                  //消息分配器



/**
 * @brief 核心线程通信初始化
 * 
 * @return net_err_t 
 */
net_err_t exmsg_init(void)
{
    dbg_info(DBG_MSG, "exmsg init");

    //初始化消息队列
    net_err_t err = fixq_init(&msg_queue, msg_tbl, EXMSG_MSG_CNT, EXMSG_BLOCKER);
    if(err<0)
    {
        dbg_error(DBG_MSG, "fixq init error");
        return err;
    }

    //初始化消息分配器
    err = mblock_init(&msg_block, msg_buffer, sizeof(exmsg_t), EXMSG_MSG_CNT, EXMSG_BLOCKER);
    if(err<0)
    {
        dbg_error(DBG_MSG, "mblock init error");
        return err;
    }

    //初始化完成
    dbg_info(DBG_MSG, "init done.");

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