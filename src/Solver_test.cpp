#include "Solver_test.h"
#include <math.h>
#include "Solver.h"
#include "Roots_printer.h"

bool make_Solve_test(Config const *const config_ptr)
{
    assert(config_ptr);

    for (size_t i = 0; i < config_ptr->test_arr_size; ++i)
    {
        Equation_roots answer = solve(&config_ptr->test_arr[i].eq, config_ptr);
        if (are_equal(&answer, &config_ptr->test_arr[i].roots, config_ptr))
        {
            continue;
        }

        printf("Test with number %zu: %LG * x2 + %LG * x + %LG with eps = %LG failed\n%-30s", i,
                config_ptr->test_arr[i].eq.a, config_ptr->test_arr[i].eq.b, config_ptr->test_arr[i].eq.c,
                config_ptr->eps, "Calculated roots are:");
        print_roots(&answer, config_ptr);
        printf("%-30s", "Must be:");
        print_roots(&config_ptr->test_arr[i].roots, config_ptr);
        return true;
    }

    return false;
}
