#include "Common.h"
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "Calculation_constants.h"

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

int are_equal(Equation_roots const *const roots1, Equation_roots const *const roots2)
{
    assert(roots1 and roots2);

    if (roots1->cnt_roots == roots2->cnt_roots)
    {
        switch (roots1->cnt_roots)
        {
            case ANY_NUMBER_IS_ROOT:
            case NO_ROOTS:
                return roots1->cnt_roots == roots2->cnt_roots;

            case ONE_ROOT:
                assert(isfinite(roots1->root1) and isfinite(roots2->root1));

                return is_nil(roots1->root1 - roots2->root1);

            case TWO_ROOTS:
                assert(isfinite(roots1->root1) and isfinite(roots1->root2) and
                       isfinite(roots2->root1) and isfinite(roots2->root2));

                return is_nil(roots1->root1 - roots2->root1) and is_nil(roots1->root2 - roots2->root2) or
                       is_nil(roots1->root1 - roots2->root2) and is_nil(roots1->root2 - roots2->root1);

            default:
                assert(0);
                break;
        }
    }
    else
    {
        return 0;
    }
}
