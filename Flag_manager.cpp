#include "Flag_manager.h"
#include <string.h>
#include <stdlib.h>
#include "Calculation_constants.h"

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
           "--eps" , "Sets the value of eps (acceptable error)");
    return construct_User_error(NORMAL_TERMINATION, 0);
}

[[nodiscard]] static User_error set_eps_config(char const *const **const str_ptr_ptr)
{
    assert(str_ptr_ptr and *str_ptr_ptr and !strcmp(**str_ptr_ptr, "--eps"));

    char *last_ptr = nullptr;
    set_eps(strtold(*++*str_ptr_ptr, &last_ptr));

    assert(last_ptr);

    if (*last_ptr != '\0')
    {
        return construct_User_error(INCORRECT_OPTION_ARGUMENT, 2, "--eps", **str_ptr_ptr);
    }

    return construct_User_error(NO_ERROR, 0);
}

[[nodiscard]] User_error set_config(int const argc, char const *const *const argv)
{
    assert(argc > 0 and argv);

    for (char const *const *str_ptr = argv + 1; str_ptr != argv + argc; ++str_ptr)
    {
        assert(str_ptr);

        User_error new_option = construct_User_error(INVALID_ERROR, 0);
        if (!strcmp(*str_ptr, "--help"))
        {
            copy_User_error(&new_option, &set_help_config(&str_ptr));
        }
        else if (!strcmp(*str_ptr, "--eps"))
        {
            copy_User_error(&new_option, &set_eps_config(&str_ptr));
        }
        else
        {
            copy_User_error(&new_option, &construct_User_error(UNKNOWN_OPTION, 1, *str_ptr));
        }

        if (new_option.code != NO_ERROR)
        {
            return new_option;
        }

        destruct_User_error(&new_option);
    }

    return construct_User_error(NO_ERROR, 0);
}
