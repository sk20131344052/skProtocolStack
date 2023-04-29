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
#include "sys_plat.h"

int main (void) 
{
	printf("Hello, world");

	//打开物理网卡, 设置好硬件地址
	pcap_t *pcap = pcap_device_open(netdev0_phy_ip, netdev0_hwaddr);

	while (pcap)
	{
		static uint8_t buffer[1024];
		static int count = 0;

		plat_printf("begin test: %d\n", count++);

		//创建待发送的数据
		for(int i=0; i<sizeof(buffer); i++)
		{
			buffer[i] = i;
		}

		//发送数据包
		if(pcap_inject(pcap, buffer, sizeof(buffer)) == -1)
		{
			plat_printf("pcap send: send packet failed!:%s\n", pcap_geterr(pcap));
			plat_printf("pcap_send: pcaket size %d\n", (int)sizeof(buffer));
			break;
		}

		//延时一会儿, 避免CPU负载过高
		sys_sleep(10);
	}
	

	return 0;
}