#include "Common.h"
#include <stdarg.h>
#include <string.h>

[[nodiscard]] User_error construct_User_error(User_error_code const code, int const str_cnt, ...)
{
    char **data = (char **)calloc(str_cnt, sizeof(char *));
    va_list arg_list = nullptr; //TODO - very strange
    va_start(arg_list, str_cnt);
    for (int i = 0; i < str_cnt; ++i)
    {
        data[i] = strdup(va_arg(arg_list, char const *));
    }
    va_end(arg_list);
    return User_error{data, code, str_cnt, 1};
}

void destruct_User_error(User_error *const ptr)
{
    assert(ptr and ptr->valid);

    ptr->valid = 0;
    for (int i = 0; i < ptr->str_cnt; ++i)
    {
        assert(ptr and ptr->data and ptr->data[i]);

        free(ptr->data[i]);
    }

    assert(ptr and ptr->data);

    free(ptr->data);
    return;
}

void copy_User_error (User_error *const to, User_error const *const from)
{
    destruct_User_error(to);

    assert(from);

    if (from->valid)
    {
        to->str_cnt = from->str_cnt;
        to->valid = 1;
        to->data = (char**)calloc(from->str_cnt, sizeof(char **));
        for (int i = 0; i < from->str_cnt; ++i)
        {
            assert(from->data);

            to->data[i] = strdup(from->data[i]);
        }
    }

    return;
}
