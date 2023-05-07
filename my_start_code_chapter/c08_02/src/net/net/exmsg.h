#ifndef EXMSG_H
#define EXMSG_H

#include "net_err.h"

/**
 * @brief 传递给核心线程的消息
 */
typedef struct _exmsg_t
{
    //消息类型
    enum
    {
        NET_EXMSG_NETIF_IN,  // 网络接口数据消息
    }type;

}exmsg_t;



net_err_t exmsg_init(void);
net_err_t exmsg_start(void);


#endif