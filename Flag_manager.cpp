#include "Flag_manager.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Calculation_constants.h"

enum Option
{
    HELP_OPTION,
    EPS_OPTION,
    __OPTION_COUNT
};

static User_error set_help_config()
{
    printf("Usage: square.exe [options] file...\nOptions:\n"
           "\t%-10s %s\n" "\t%-10s %s\n",
           "--help", "Display the information",
           "--eps" , "Sets the value of eps (acceptable error)");
    return User_error{NORMAL_TERMINATION, 0, nullptr};
}

static User_error set_eps_config(char ***const flag_ptr_ptr)
{
    assert(flag_ptr_ptr and *flag_ptr_ptr);

    char *last_ptr = nullptr;
    set_eps(strtold(*(*flag_ptr_ptr)++, &last_ptr));

    assert(last_ptr);

    if (*last_ptr != '\0')
    {
        //assert(flag_ptr_ptr > 2);
        return User_error{INCORRECT_OPTION_ARGUMENT, 2, *flag_ptr_ptr - 2};
    }

    return User_error{NO_ERROR, 0, nullptr};
}

User_error set_config(int const argc, char *argv[])
{
    assert(argc > 0 and argv);

    int used[__OPTION_COUNT] = {};
    for (char **flag_ptr = argv + 1; flag_ptr != argv + argc;)
    {
        assert(flag_ptr);

        if (!strcmp(*flag_ptr, "--help"))
        {
            used[HELP_OPTION] = 1;
            ++flag_ptr;
        }
        else if (!strcmp(*flag_ptr, "--eps"))
        {
            set_eps_config(&++flag_ptr);
        }
        else
        {
            return User_error{UNKNOWN_OPTION, 1, flag_ptr};
        }
    }

    if (used[HELP_OPTION])
    {
        set_help_config();
        return User_error{NORMAL_TERMINATION, 0, nullptr};
    }

    return User_error{NO_ERROR, 0, nullptr};
}
