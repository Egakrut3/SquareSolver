#include "Flag_manager.h"
#include <string.h>
#include <stdlib.h>
#include "Calculation_constants.h"

enum Option
{
    HELP_OPTION,
    EPS_OPTION
};

static User_error set_help_config(char const *const **const str_ptr_ptr)
{
    assert(str_ptr_ptr and *str_ptr_ptr and !strcmp(**str_ptr_ptr, "--help"));

    printf("Usage: square.exe [options] file...\nOptions:\n"
           "\t%-10s %s\n" "\t%-10s %s\n",
           "--help", "Display the information",
           "--eps" , "Sets the value of eps (acceptable error)");
    return User_error{NORMAL_TERMINATION, nullptr};
}

static User_error set_eps_config(char const *const **const str_ptr_ptr)
{
    assert(str_ptr_ptr and *str_ptr_ptr and !strcmp(**str_ptr_ptr, "--eps"));

    char *last_ptr = nullptr;
    set_eps(strtold(*++*str_ptr_ptr, &last_ptr));

    assert(last_ptr);

    if (*last_ptr != '\0')
    {
        //TODO - make assert
        //assert(flag_ptr_ptr > 2);
        //TODO - make own User_error data
        return User_error{INCORRECT_OPTION_ARGUMENT, *str_ptr_ptr - 2};
    }

    return User_error{NO_ERROR, nullptr};
}

User_error set_config(int const argc, char const *const argv[])
{
    assert(argc > 0 and argv);

    for (char const *const *str_ptr = argv + 1; str_ptr != argv + argc; ++str_ptr)
    {
        assert(str_ptr);

        User_error new_option = {INVALID_ERROR, nullptr};
        if (!strcmp(*str_ptr, "--help"))
        {
            new_option = set_help_config(&str_ptr);
        }
        else if (!strcmp(*str_ptr, "--eps"))
        {
            new_option = set_eps_config(&str_ptr);
        }
        else
        {
            //TODO - make own User_error data
            new_option = User_error{UNKNOWN_OPTION, str_ptr};
        }

        if (new_option.code != NO_ERROR)
        {
            return new_option;
        }
    }

    return User_error{NO_ERROR, nullptr};
}
