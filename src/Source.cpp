//TODO - make documentation
//TODO - use unsigned where possible
//TODO - make file in-/out- put
//TODO - Make colored printf library

#include "Common.h"
#include "Option_manager.h"
#include "User_error_handler.h"
#include "Coefficient_scaner.h"
#include "Solver.h"
#include "Solver_test.h"
#include "Roots_printer.h"

#define HANDLE_USER_ERROR(__ERROR) do {   \
    User_error cur_error = __ERROR;       \
    if (handle_user_error(&cur_error))    \
    {                                     \
        destruct_User_error(&cur_error);  \
        return 0;                         \
    }                                     \
                                          \
    destruct_User_error(&cur_error);      \
} while(0)

int main(int const argc, char **argv)
{
#ifdef _DEBUG

    if (make_Solve_test())
    {
        return 1;
    }

#endif

    HANDLE_USER_ERROR(set_config(argc, argv));

    Square_equation eq = scan_square_coefficients();
    Equation_roots roots = solve(&eq);
    print_roots(&roots);

    printf("\n\n\nCOMMIT GITHUB");
    return 0;
}
