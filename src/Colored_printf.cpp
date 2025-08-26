#include "Colored_printf.h"
#include <stdio.h>
#include <stdarg.h>

int colored_printf(Color const color, char const *const format, ...)
{
    printf("\033[0%dm", 30 + color);

    va_list arg_list = nullptr;
    va_start(arg_list, format);
    int const ret_value = vprintf(format, arg_list);
    va_end(arg_list);

    printf("\033[0m");
    return ret_value;
}
