#include "net.h"
#include "net_plat.h"
#include "exmsg.h"

/**
 * @brief 协议栈初始化
 * 
 * @return net_err_t 
 */
net_err_t net_init(void)
{
    net_plat_init();
    exmsg_init();
    return NET_ERR_OK;
}

/**
 * @brief 启动协议栈
 * 
 * @return net_err_t 
 */
net_err_t net_start(void)
{
    //启动消息传递机制
    exmsg_start();
    return NET_ERR_OK;
}
