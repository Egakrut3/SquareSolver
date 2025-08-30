/*! \file */

#include "Solver_test.h"
#include <math.h>
#include "Calculation_constants.h"
#include "Solver.h"
#include "Roots_printer.h"

/*!
 *Checks solve function for errors

 *\param[in] config_ptr A pointer to config object that determines behaviour of program

 *\return Returns true if any error was found and 0 otherwise
 */
bool make_Solve_test(Config const *const config_ptr)
{
    assert(config_ptr);

    for (size_t i = 0; i < config_ptr->test_arr_size; ++i)
    {
        Equation_roots answer = solve(&config_ptr->test_arr[i].eq);
        if (are_equal(&answer, &config_ptr->test_arr[i].roots))
        {
            continue;
        }

        printf("Test with number %zu: %LG * x2 + %LG * x + %LG with eps = %LG failed\n%-30s", i,
                test_arr[i].eq.a, test_arr[i].eq.b, test_arr[i].eq.c,
                config_ptr->cur_eps, "Calculated roots are:");
        print_roots(&answer);
        printf("%-30s", "Must be:");
        print_roots(&test_arr[i].roots);
        return 1;
    }

    return 0;
}
