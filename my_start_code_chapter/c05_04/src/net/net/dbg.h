#ifndef DBG_H
#define DBG_H

//调试信息的显示样式设置
#define DBG_STYLE_RESET  "\033[0m"   //复位显示
#define DBG_STYLE_ERROR  "\033[31m"  //红色显示
#define DBG_STYLE_WARING "\033[33m" //黄色显示

// 开启的信息输出配置，值越大，输出的调试信息越多
#define DBG_LEVEL_NONE           0         // 不开启任何输出
#define DBG_LEVEL_ERROR          1         // 只开启错误信息输出
#define DBG_LEVEL_WARNING        2         // 开启错误和警告信息输出
#define DBG_LEVEL_INFO           3         // 开启错误、警告、一般信息输出


/**
 * @brief 打印调试信息
 * 
 * @param file 
 * @param func 
 * @param line 
 * @param fmt 
 * @param ... 
 */
void dbg_print(int m_level, int s_level, const char *file, const char *func, int line, const char *fmt, ...);


#define dbg_error(module, fmt, ...) dbg_print(module, DBG_LEVEL_ERROR,__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define dbg_warning(module, fmt, ...) dbg_print(module, DBG_LEVEL_WARNING,__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define dbg_info(module, fmt, ...) dbg_print(module, DBG_LEVEL_INFO,__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)


#define dbg_assert(expr, msg)   { \
    if(!(expr)) { \
        dbg_print(DBG_LEVEL_ERROR, DBG_LEVEL_ERROR, __FILE__, __FUNCTIONW__, __LINE__, "assert failed:"#expr","msg); \
        while(1);   \
    }   \
}

#endif