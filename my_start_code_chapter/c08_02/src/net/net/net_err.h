/**
 * @file net_err.h
 * @author your name (you@domain.com)
 * @brief   错误类型和常量
 * @version 0.1
 * @date 2023-04-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef NET_ERR_H
#define NET_ERR_H

/**
 * @brief 错误码以及类型
 * 
 */
typedef enum _net_err_t
{
    NET_ERR_OK = 0, //没有错误
    NET_ERR_SYS = -1, //操作系统错误
}net_err_t;

#endif