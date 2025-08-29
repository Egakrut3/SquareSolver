/*! \file */

#include "Common.h"
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "Calculation_constants.h"

/*!
 *Extenranal constructor for User_error

 *\param[in] code A code of error
 *\param[in] str_cnt Count of strings to be passed to User_error.data
 *\param[in] others Strings to be passed to User_error.data themselves

 *\return Constructed User_error
 */
[[nodiscard]] User_error construct_User_error(User_error_code const code, size_t const str_cnt, ...)
{
    assert(str_cnt >= 0);

    if (!str_cnt)
    {
        return User_error{nullptr, code, str_cnt, 1};
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
    return User_error{data, code, str_cnt, 1};
}

/*!
 *External destructor for User_error

 *\param[in, out] ptr A pointer to User_error to be destructed
 */
void destruct_User_error(User_error *const ptr)
{
    assert(ptr and ptr->valid and ptr->str_cnt >= 0);

    ptr->valid = 0;
    for (size_t i = 0; i < ptr->str_cnt; ++i)
    {
        assert(ptr->data and ptr->data[i]);

        free(ptr->data[i]);
    }

    assert(ptr);

    free(ptr->data);
    return;
}

/*!
 *External "assignement operator" for User_error

 *\param[out] to A pointer to destination User_error
 *\param[in] from A pointer to source User_error
 */
void copy_User_error (User_error *const to, User_error const *const from)
{
    destruct_User_error(to);

    assert(to and from);

    if (from->valid)
    {
        to->code = from->code;
        to->str_cnt = from->str_cnt;
        to->valid = from->valid;

        if (!from->str_cnt)
        {
            to->data = nullptr;
            return;
        }

        to->data = (char**)calloc(from->str_cnt, sizeof(char **));

        assert(to->data);

        for (size_t i = 0; i < from->str_cnt; ++i)
        {
            assert(from->data and from->data[i]);

            to->data[i] = strdup(from->data[i]);

            assert(to->data and to->data[i]);
        }
    }

    return;
}

/*!
 *Checks whether two sets of roots are equal or not

 *\param[in] roots1 The first set of roots
 *\param[in] roots The second set of roots

 *\return Returns 1 if sets considered equal and 0 otherwise
 */
int8_t are_equal(Equation_roots const *const roots1, Equation_roots const *const roots2)
{
    assert(roots1 and roots2);

    if (roots1->cnt_roots == roots2->cnt_roots)
    {
        switch (roots1->cnt_roots)
        {
            case ANY_NUMBER_IS_ROOT:
            case DEGENERATE_NO_ROOTS:
            case SQUARE_NO_ROOTS:
                return 1;

            case LINEAR_ONE_ROOT:
            case SQUARE_ONE_ROOT:
                assert(isfinite(roots1->root1) and isfinite(roots2->root1) and
                       isnan(roots1->root2)    and isnan(roots2->root2));

                return is_nil(roots1->root1 - roots2->root1);

            case SQUARE_TWO_ROOTS:
                assert(isfinite(roots1->root1) and isfinite(roots1->root2) and
                       isfinite(roots2->root1) and isfinite(roots2->root2));

                return (is_nil(roots1->root1 - roots2->root1) and is_nil(roots1->root2 - roots2->root2)) or
                       (is_nil(roots1->root1 - roots2->root2) and is_nil(roots1->root2 - roots2->root1));

            default:
                assert(0);
                break;
        }
    }

    return 0;
}
