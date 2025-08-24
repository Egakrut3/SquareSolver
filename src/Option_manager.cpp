#include "Option_manager.h"
#include <string.h>
#include <stdlib.h>
#include "Calculation_constants.h"
#include <math.h>

enum Option
{
    HELP_OPTION,
    EPS_OPTION
};

[[nodiscard]] static User_error set_help_config(char const *const **const str_ptr_ptr)
{
    assert(str_ptr_ptr and *str_ptr_ptr and !strcmp(**str_ptr_ptr, "--help"));

    printf("Usage: square.exe [options] file...\nOptions:\n"
           "\t%-10s %s\n" "\t%-10s %s\n",
           "--help", "Display the information",
           "--eps" , "Sets the value of eps (acceptable error) by followed parameter");
    return construct_User_error(NORMAL_TERMINATION, 0);
}

[[nodiscard]] static User_error set_eps_config(char const *const **const str_ptr_ptr, char const *const *const end_ptr)
{
    assert(str_ptr_ptr and *str_ptr_ptr and !strcmp(**str_ptr_ptr, "--eps") and end_ptr);

    if (++*str_ptr_ptr == end_ptr)
    {
        return construct_User_error(NOT_ENOUGH_OPTION_ARGUMENTS, 1, "--eps");
    }

    char *last_ptr = nullptr;
    ld const new_eps = strtold(**str_ptr_ptr, &last_ptr);

    assert(last_ptr);

    if (*last_ptr == '\0' and isfinite(new_eps) and new_eps >= 0)
    {
        set_eps(new_eps);
        return construct_User_error(NO_ERROR, 0);
    }
    else
    {
        return construct_User_error(INCORRECT_OPTION_ARGUMENT, 2, "--eps", **str_ptr_ptr);
    }
}

[[nodiscard]] User_error set_config(int const argc, char const *const *const argv)
{
    assert(argc > 0 and argv);

    char const *const *const end_ptr = argv + argc;

    for (char const *const *str_ptr = argv + 1; str_ptr != end_ptr; ++str_ptr)
    {
        User_error new_option = construct_User_error(INVALID_ERROR, 0);

        assert(str_ptr);

        if (!strcmp(*str_ptr, "--help"))
        {
            User_error new_error = set_help_config(&str_ptr);
            copy_User_error(&new_option, &new_error);
            destruct_User_error(&new_error);
        }
        else if (!strcmp(*str_ptr, "--eps"))
        {
            User_error new_error = set_eps_config(&str_ptr, end_ptr);
            copy_User_error(&new_option, &new_error);
            destruct_User_error(&new_error);
        }
        else
        {
            User_error new_error = construct_User_error(UNKNOWN_OPTION, 1, *str_ptr);
            copy_User_error(&new_option, &new_error);
            destruct_User_error(&new_error);
        }

        if (new_option.code != NO_ERROR)
        {
            return new_option;
        }

        destruct_User_error(&new_option);
    }

    return construct_User_error(NO_ERROR, 0);
}
