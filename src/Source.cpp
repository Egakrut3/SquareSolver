//TODO - make file in-/out-put
//TODO - make documentation

#include "Common.h"
#include "Option_manager.h"
#include "User_error_handler.h"
#include "Solve_test.h"
#include "Input.h"
#include "Solve.h"
#include "Output.h"

int main(int const argc, char **argv)
{
    User_error cur_error = set_config(argc, argv);
    if (handle_user_error(&cur_error))
    {
        destruct_User_error(&cur_error);
        return 0;
    }
    destruct_User_error(&cur_error);

#ifdef _DEBUG

    if (make_Solve_test())
    {
        return 1;
    }

#endif

    Equation_roots roots = solve(get_input());
    make_output(&roots);

    return 0;
}
