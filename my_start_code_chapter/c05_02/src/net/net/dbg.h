#ifndef DBG_H
#define DBG_H

//调试信息的显示样式设置
#define DBG_STYLE_RESET  "\033[0m"   //复位显示
#define DBG_STYLE_ERROR  "\033[31m"  //红色显示
#define DBG_STYLE_WARING "\033[33m" //黄色显示



/**
 * @brief 打印调试信息
 * 
 * @param file 
 * @param func 
 * @param line 
 * @param fmt 
 * @param ... 
 */
void dbg_print(const char *file, const char *func, int line, const char *fmt, ...);



#define dbg_info(fmt, ...) dbg_print(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)


#endif