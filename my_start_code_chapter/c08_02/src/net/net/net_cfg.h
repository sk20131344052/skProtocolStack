#ifndef NET_CFG_H
#define NET_CFG_H

// 调试信息输出
#define DBG_MBLOCK  DBG_LEVEL_INFO  // 内存块管理器
#define DBG_QUEUE           DBG_LEVEL_INFO          // 定长存储块
#define DBG_MSG             DBG_LEVEL_INFO          // 消息通信




#define EXMSG_MSG_CNT        10                  // 消息缓冲区大小
#define EXMSG_BLOCKER        NLOCKER_THREAD      // 核心线程的锁类型

#endif