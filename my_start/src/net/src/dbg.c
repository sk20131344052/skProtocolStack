#include <string.h>
#include <stdarg.h>
#include "dbg.h"
#include "net_plat.h"


void dbg_print(const char *file, const char *func, int line, const char *fmt, ...)
{
    // 定位到文件名部分，因为file传输的是完整的文件路径，太长了
    const char *end = file + plat_strlen(file);
    while (end >= file)
    {
        if((*end == '\\') || (*end == '/'))
        {
            break;
        }
        end--;
    }

    end++;

    // 每行信息提示的开头
    plat_printf("(%s-%s-%d):", end, func, line);

    char str_buf[128];
    va_list args;
    
    // 具体的信息
    va_start(args, fmt);
    plat_vsprintf(str_buf, fmt, args);
    plat_printf("%s\n", str_buf);
    va_end(args);
}

