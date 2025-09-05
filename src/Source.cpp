/*! \file */

#include "Common.h"
#include "Option_manager.h"
#include "User_error_handler.h"
#include "Coefficient_scaner.h"
#include "Solver.h"
#include "Solver_test.h"
#include "Roots_printer.h"

/*!
 *A macros to handle an error, destruct it and finish the program if necessary by one row
 */
#define HANDLE_USER_ERROR(__ERROR) do {  \
    User_error cur_error = __ERROR;      \
    if (handle_user_error(&cur_error))   \
    {                                    \
        destruct_User_error(&cur_error); \
        return 0;                        \
    }                                    \
                                         \
    destruct_User_error(&cur_error);     \
} while(false)

/*!
 *An entry point for the program

 *\param[in] argc Count of command-line arguments
 *\param[in] argv Command-line arguments themselves
 */
int main(int const argc, char const *const * const argv)
{
    Config cur_config = Config{0, 0, nullptr, nullptr, nullptr, false, true};
    HANDLE_USER_ERROR(set_config(argc, argv, &cur_config));

#ifdef _DEBUG

    if (make_Solve_test(&cur_config))
    {
        return 1;
    }

#endif

    if (cur_config.is_help)
    {
        return 0;
    }

    Square_equation eq = Square_equation{0, 0, 0};
    HANDLE_USER_ERROR(scan_square_coefficients(&eq, &cur_config));
    Equation_roots const roots = solve(&eq, &cur_config);
    print_roots(&roots, &cur_config);

    destruct_Config(&cur_config);
    printf("\n\n\nCOMMIT GITHUB\n\n");
    return 0;
}
