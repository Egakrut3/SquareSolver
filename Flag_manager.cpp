#include "Flag_manager.h"
#include "Calculation_constants.h"
#include <string.h>
#include <stdlib.h>

static void set_eps_config(char const *const **const flag_ptr_ptr)
{
    set_eps(strtold(*(*flag_ptr_ptr)++, nullptr));
    return;
}

void set_config(int const argc, char const *const argv[])
{
    for (char const *const *flag_ptr = argv; flag_ptr != argv + argc;)
    {
        if (strcmp(*flag_ptr, "--eps"))
        {
            set_eps_config(&++flag_ptr);
        }
        else
        {
            //abort();
        }
    }
    return;
}
