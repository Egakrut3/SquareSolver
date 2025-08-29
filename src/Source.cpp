/*! \file */

//TODO - Make file in-/out- put
//TODO - Make colored printf library
//TODO - Merge branches in git

#include "Common.h"
#include "Option_manager.h"
#include "User_error_handler.h"
#include "Coefficient_scaner.h"
#include "Solver.h"
#include "Solver_test.h"
#include "Roots_printer.h"

/*!
 *A macro to handle an error, destruct it and finish the program if necessary by one row
 */
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

/*!
 *An entry point for the program

 *\param[in] argc Count of command-line arguments
 *\param[in] argv Command-line arguments themselves
 */
int main(size_t const argc, char **argv)
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
