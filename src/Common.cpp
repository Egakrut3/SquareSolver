#include "Common.h"
#include <stdarg.h>
#include <string.h>

[[nodiscard]] User_error construct_User_error(User_error_code const code, int const str_cnt, ...)
{
    char **data = (char **)calloc(str_cnt, sizeof(char *));
    va_list arg_list = nullptr;
    va_start(arg_list, str_cnt);
    for (int i = 0; i < str_cnt; ++i)
    {
        char const *const new_str = va_arg(arg_list, char const *);
        data[i] = strdup(new_str);
    }
    va_end(arg_list);
    return User_error{data, code, str_cnt, 1};
}

void destruct_User_error(User_error *const ptr)
{
    assert(ptr and ptr->valid);

    ptr->valid = 0;

    assert(ptr and ptr->data);

    for (int i = 0; i < ptr->str_cnt; ++i)
    {
        assert(ptr->data[i]);

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
        to->code = from->code;
        to->str_cnt = from->str_cnt;
        to->valid = 1;
        to->data = (char**)calloc(from->str_cnt, sizeof(char **));

        assert(from->data);

        for (int i = 0; i < from->str_cnt; ++i)
        {
            assert(from->data[i]);

            to->data[i] = strdup(from->data[i]);
        }
    }

    return;
}
