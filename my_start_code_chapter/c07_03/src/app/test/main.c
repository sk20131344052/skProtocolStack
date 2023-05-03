﻿/**
 * @file main.c
 * @author lishutong (527676163@qq.com)
 * @brief 测试主程序，完成一些简单的测试主程序
 * @version 0.1
 * @date 2022-10-23
 *
 * @copyright Copyright (c) 2022
 * @note 该源码配套相应的视频课程，请见源码仓库下面的README.md
 */
#include <stdio.h>
#include "netif_pcap.h"
#include "sys_plat.h"
#include "echo/tcp_echo_client.h"
#include "echo/tcp_echo_server.h"
#include "net.h"
#include "dbg.h"
#include "nlist.h"
#include "mblock.h"

static sys_sem_t sem;
static sys_mutex_t mutex;

static char buffer[100];
static int write_idx, read_idx, total;	//写索引和读索引 总计数
static sys_sem_t read_sem;	//读信号量
static sys_sem_t write_sem; //写信号量

static int countTest; //计数器


/**
 * @brief 网络设备初始化
 * 
 * @return net_err_t 
 */
net_err_t net_dev_init(void)
{
	netif_pcap_open();
	return NET_ERR_OK;
}


#define DBG_TEST    DBG_LEVEL_INFO
//#define DBG_TEST    DBG_LEVEL_WARNING
//#define DBG_TEST    DBG_LEVEL_ERROR
//#define DBG_TEST    DBG_LEVEL_NONE


/**
 * @brief 测试结点
 */
typedef struct _tnode_t
{
	int id;
	nlist_node_t node;
}tnode_t;



/**
 * @brief 链表访问测试
 */
void nlist_test(void)
{
	#define NODE_CNT	8

	tnode_t node[NODE_CNT];
	nlist_t list;
	nlist_node_t *p;

	nlist_init(&list);

	//头部插入
	for(int i=0; i<NODE_CNT; i++)
	{
		node[i].id = i;
		nlist_insert_first(&list, &node[i].node);
	}

	// 遍历打印
	plat_printf("insert first\n");
	nlist_for_each(p, &list)
	{
		tnode_t *tnode = nlist_entry(p, tnode_t, node);
		plat_printf("id:%d\n", tnode->id);
	}

    // 头部移除
    plat_printf("remove first\n");
    for (int i = 0; i < NODE_CNT; i++) 
	{
        p = nlist_remove_first(&list);
        plat_printf("id:%d\n", nlist_entry(p, tnode_t, node)->id);
   	}


    // 尾部插入
    for (int i = 0; i < NODE_CNT; i++)
	{
        nlist_insert_last(&list, &node[i].node);
    }

    // 遍历打印
    plat_printf("insert last\n");
    nlist_for_each(p, &list) 
	{
        tnode_t * tnode = nlist_entry(p, tnode_t, node);
        plat_printf("id:%d\n", tnode->id);
    }

    // 尾部移除
    plat_printf("remove last\n");
    for (int i = 0; i < NODE_CNT; i++) 
	{
        p = nlist_remove_last(&list);
        plat_printf("id:%d\n", nlist_entry(p, tnode_t, node)->id);
   }

 	// 插入到指定结点之后
    plat_printf("insert after\n");
    for (int i = 0; i < NODE_CNT; i++) 
	{
        nlist_insert_after(&list, nlist_first(&list), &node[i].node);
    }

    // 遍历打印
    nlist_for_each(p, &list) 
	{
        tnode_t * tnode = nlist_entry(p, tnode_t, node);
        plat_printf("id:%d\n", tnode->id);
    }


}



void mblock_test(void)
{
	static uint8_t buffer[10][100];
	mblock_t blist;

	mblock_init(&blist, buffer, 100, 10, NLOCKER_THREAD);
}



/**
 * @brief 基本测试
 */
void basic_test(void) 
{
    nlist_test();
	mblock_test();
}



int main (void) 
{
	
	//基础测试
	basic_test();


    // 不同等级调试输出测试
    // dbg_info(DBG_TEST, "info");
    // dbg_warning(DBG_TEST, "warning");
    // dbg_error(DBG_TEST, "error");

	//断言调试
    // dbg_assert(1==1, "failed");
    // dbg_assert(1==0, "failed")

	//初始化协议栈
	net_init();

	//启动协议栈
	net_start();

	//初始化网络接口
	net_dev_init();


	while (1)
	{
		sys_sleep(10);
	}
	

	

	return 0;
}