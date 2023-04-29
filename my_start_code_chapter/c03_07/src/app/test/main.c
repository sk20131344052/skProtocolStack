/**
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

static sys_sem_t sem;
static sys_mutex_t mutex;

static char buffer[100];
static int write_idx, read_idx;	//写索引和读索引
static sys_sem_t read_sem;	//读信号量

static int countTest; //计数器

/**
 * @brief 
 * 线程1
 * @return int 
 */
void thread1_entry(void* arg)
{
	//不断读取数据
	for(int i=0; i<2*sizeof(buffer); i++)
	{
		// 等待有数据，即读信号量中的数据资源计数不为0
		sys_sem_wait(read_sem, 0);

		//取出一个数据
		unsigned char data = buffer[read_idx++];
		if(read_idx>=sizeof(buffer))
		{
			read_idx = 0;
		}

		plat_printf("thread 1 read data %d\n", data);

		//延时一会儿, 让读取的速度慢一点
		sys_sleep(200);
	}

	
}

/**
 * @brief 
 * 线程2
 * @return int 
 */
void thread2_entry(void* arg)
{
	sys_sleep(100);

	//连续写200次，由于中间没有printf, 延时， 所以写的速度是比较快的
	for(int i=0; i<2*sizeof(buffer); i++)
	{
		//不为0则将数据写入
		buffer[write_idx++] = i;
		if(write_idx>=sizeof(buffer))
		{
			write_idx=0;
		}

		plat_printf("thread 2 write data %d\n", i);

		// 通知另一个线程可以进行读取，但具体什么时候读则不确定
		sys_sem_notify(read_sem);

		//让写的速度比读取更快
		sys_sleep(100);
	}


	
}



int main (void) 
{
	//注意放在线程创建的前面, 以便线程运行前就准备好
	sem = sys_sem_create(0);
	mutex = sys_mutex_create();
	read_sem = sys_sem_create(0);

	sys_thread_create(thread1_entry, "AAAAA");
	sys_thread_create(thread2_entry, "BBBBB");


	// printf("Hello, world\n");

	//打开物理网卡, 设置好硬件地址
	pcap_t *pcap = pcap_device_open(netdev0_phy_ip, netdev0_hwaddr);

	while (pcap)
	{
		static uint8_t buffer[1024];
		static int count = 0;
		struct pcap_pkthdr *pkthdr;
		const uint8_t *pkt_data;

		plat_printf("begin test: %d\n", count++);

		//以下测试程序, 读取网络上的广播包, 然后再发送出去
		//读取数据包
		if(pcap_next_ex(pcap, &pkthdr, &pkt_data) != 1)
		{
			continue;
		}

		//稍微修改一下, 再发送
		int len = pkthdr->len > sizeof(buffer) ? sizeof(buffer) : pkthdr->len;
		plat_memcpy(buffer, pkt_data, len);
		buffer[0] = 1;
		buffer[1] = 2;


		//发送数据包
		if(pcap_inject(pcap, buffer, sizeof(buffer)) == -1)
		{
			plat_printf("pcap send: send packet failed!:%s\n", pcap_geterr(pcap));
			plat_printf("pcap_send: pcaket size %d\n", (int)sizeof(buffer));
			break;
		}

	}
	

	return 0;
}