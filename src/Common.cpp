#include "Common.h"
#include <stdarg.h>
#include <string.h>
#include <math.h>

[[nodiscard]] User_error construct_User_error(User_error_code const code, size_t const str_cnt, ...)
{
    if (!str_cnt)
    {
        return User_error{str_cnt, nullptr, code, true};
    }

    char **data = (char **)calloc(str_cnt, sizeof(char *));

    assert(data);

    va_list arg_list = nullptr;
    va_start(arg_list, str_cnt);
    for (size_t i = 0; i < str_cnt; ++i)
    {
        char const *const new_str = va_arg(arg_list, char const *);

        assert(new_str);

        data[i] = strdup(new_str);

        assert(data[i]);
    }
    va_end(arg_list);
    return User_error{str_cnt, data, code, true};
}

void destruct_User_error(User_error *const error_ptr)
{
    assert(error_ptr and error_ptr->valid);

    error_ptr->valid = 0;
    for (size_t i = 0; i < error_ptr->str_cnt; ++i)
    {
        assert(error_ptr->data and error_ptr->data[i]);

        free(error_ptr->data[i]);
    }

    free(error_ptr->data);
    return;
}

Cnt_roots strto_Cnt_roots(char const *const str)
{
    if (!strcmp(str, "ANY_NUMBER_IS_ROOT"))
    {
        return ANY_NUMBER_IS_ROOT;
    }

    if (!strcmp(str, "DEGENERATE_NO_ROOTS"))
    {
        return DEGENERATE_NO_ROOTS;
    }

    if (!strcmp(str, "SQUARE_NO_ROOTS"))
    {
        return SQUARE_NO_ROOTS;
    }

    if (!strcmp(str, "LINEAR_ONE_ROOT"))
    {
        return LINEAR_ONE_ROOT;
    }

    if (!strcmp(str, "SQUARE_ONE_ROOT"))
    {
        return SQUARE_ONE_ROOT;
    }

    if (!strcmp(str, "SQUARE_TWO_ROOTS"))
    {
        return SQUARE_TWO_ROOTS;
    }

    return __INVALID_COUNT;
}

void destruct_Config(Config *const config_ptr)
{
    assert(config_ptr and config_ptr->is_valid);

    config_ptr->is_valid = false;
    free(config_ptr->test_arr);
    if (config_ptr->input_stream and config_ptr->input_stream != stdin)
    {
        fclose(config_ptr->input_stream);
    }

    if (config_ptr->output_stream and config_ptr->output_stream != stdout)
    {
        fclose(config_ptr->output_stream);
    }

    return;
}

bool is_nil(ld const x, Config const *const config_ptr)
{
    assert(config_ptr and config_ptr->is_valid);

    return fabsl(x) <= config_ptr->eps;
}

bool are_equal(Equation_roots const *const roots1_ptr, Equation_roots const *const roots2_ptr,
               Config const *const config_ptr)
{
    assert(roots1_ptr and roots2_ptr);

    if (roots1_ptr->cnt_roots != roots2_ptr->cnt_roots)
    {
        return false;
    }

    switch (roots1_ptr->cnt_roots)
    {
        case ANY_NUMBER_IS_ROOT:
        case DEGENERATE_NO_ROOTS:
        case SQUARE_NO_ROOTS:
            assert(isnan(roots1_ptr->root1) and isnan(roots1_ptr->root2) and
                   isnan(roots2_ptr->root1) and isnan(roots2_ptr->root2));

            return true;

        case LINEAR_ONE_ROOT:
        case SQUARE_ONE_ROOT:
            assert(isfinite(roots1_ptr->root1) and isfinite(roots2_ptr->root1) and
                    isnan(roots1_ptr->root2) and isnan(roots2_ptr->root2));

            return is_nil(roots1_ptr->root1 - roots2_ptr->root1, config_ptr);

        case SQUARE_TWO_ROOTS:
            assert(isfinite(roots1_ptr->root1) and isfinite(roots1_ptr->root2) and
                    isfinite(roots2_ptr->root1) and isfinite(roots2_ptr->root2));

            return (is_nil(roots1_ptr->root1 - roots2_ptr->root1, config_ptr) and
                    is_nil(roots1_ptr->root2 - roots2_ptr->root2, config_ptr)) or
                    (is_nil(roots1_ptr->root1 - roots2_ptr->root2, config_ptr) and
                    is_nil(roots1_ptr->root2 - roots2_ptr->root1, config_ptr));

        case __INVALID_COUNT:
        default:
            assert(0);

            break;
    }

    assert(0);

    return false;
}
