/*! \file */

//TODO -  make tests from file
//TODO - Use fized size types

#include "Solver_test.h"
#include <math.h>
#include "Calculation_constants.h"
#include "Solver.h"
#include "Roots_printer.h"

/*!
 *Contains all tests
 */
static Solve_test_instance const test_arr[] = {
       Solve_test_instance{Square_equation{1, 2, 1}, Equation_roots{-1, NAN, SQUARE_ONE_ROOT}},
       Solve_test_instance{Square_equation{1, -2, 1}, Equation_roots{1, NAN, SQUARE_ONE_ROOT}},
       Solve_test_instance{Square_equation{1, 5, 6}, Equation_roots{-2, -3, SQUARE_TWO_ROOTS}},
       Solve_test_instance{Square_equation{1, -5, 6}, Equation_roots{2, 3, SQUARE_TWO_ROOTS}},
       Solve_test_instance{Square_equation{1, 2, 2}, Equation_roots{NAN, NAN, SQUARE_NO_ROOTS}},
       Solve_test_instance{Square_equation{1, 2, 1.001}, Equation_roots{NAN, NAN, SQUARE_NO_ROOTS}},
       Solve_test_instance{Square_equation{-1, -2, -1}, Equation_roots{-1, NAN, SQUARE_ONE_ROOT}},
       Solve_test_instance{Square_equation{-1, 2, -1}, Equation_roots{1, NAN, SQUARE_ONE_ROOT}},
       Solve_test_instance{Square_equation{-1, -5, -6}, Equation_roots{-2, -3, SQUARE_TWO_ROOTS}},
       Solve_test_instance{Square_equation{-1, 5, -6}, Equation_roots{2, 3, SQUARE_TWO_ROOTS}},
       Solve_test_instance{Square_equation{-1, -2, -2}, Equation_roots{NAN, NAN, SQUARE_NO_ROOTS}},
       Solve_test_instance{Square_equation{-1, -2, -1.001}, Equation_roots{NAN, NAN, SQUARE_NO_ROOTS}},

       Solve_test_instance{Square_equation{0, 2, 1}, Equation_roots{-0.5, NAN, LINEAR_ONE_ROOT}},
       Solve_test_instance{Square_equation{0, 3, 1}, Equation_roots{-0.333333333333l, NAN, LINEAR_ONE_ROOT}},
       Solve_test_instance{Square_equation{0, 1, -53}, Equation_roots{53, NAN, LINEAR_ONE_ROOT}},
       Solve_test_instance{Square_equation{0, -2, -1}, Equation_roots{-0.5, NAN, LINEAR_ONE_ROOT}},
       Solve_test_instance{Square_equation{0, -3, -1}, Equation_roots{-0.333333333333l, NAN, LINEAR_ONE_ROOT}},
       Solve_test_instance{Square_equation{0, -1, 53}, Equation_roots{53, NAN, LINEAR_ONE_ROOT}},

       Solve_test_instance{Square_equation{0, 0, 1}, Equation_roots{NAN, NAN, DEGENERATE_NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, 0.001}, Equation_roots{NAN, NAN, DEGENERATE_NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, 1'000'000}, Equation_roots{NAN, NAN, DEGENERATE_NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, -1}, Equation_roots{NAN, NAN, DEGENERATE_NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, -0.001}, Equation_roots{NAN, NAN, DEGENERATE_NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, -1'000'000}, Equation_roots{NAN, NAN, DEGENERATE_NO_ROOTS}},

       Solve_test_instance{Square_equation{0, 0, 0}, Equation_roots{NAN, NAN, ANY_NUMBER_IS_ROOT}},
       Solve_test_instance{Square_equation{-0, 0.00, 0E+195}, Equation_roots{NAN, NAN, ANY_NUMBER_IS_ROOT}},

       Solve_test_instance{Square_equation{1, -3, 0}, Equation_roots{0, 3, SQUARE_TWO_ROOTS}},
       Solve_test_instance{Square_equation{1, 0, -2}, Equation_roots{-1.4142135623730950488016887242097l, 1.4142135623730950488016887242097l, SQUARE_TWO_ROOTS}},
       Solve_test_instance{Square_equation{-0.76, 0, 0}, Equation_roots{0, NAN, SQUARE_ONE_ROOT}},
       Solve_test_instance{Square_equation{0, -3, 0}, Equation_roots{0, NAN, LINEAR_ONE_ROOT}},
};

/*!
 *Contains test eps value
 */
static ld const eps_test[] = {0.000'1, 0.000'001, 0.000'000'001, 0.000'000'000'001, 0.000'000'000'001};

/*!
 *Contains count of tests
 */
static size_t const SOLVE_TEST_CNT = sizeof test_arr / sizeof *test_arr;

/*!
 *Contains count of test eps values
 */
static size_t const CNT_EPS = sizeof eps_test / sizeof *eps_test;

/*!
 *Checks every test with eps have previosly set

 *\param[in] cur_eps Actual eps value

 *\return Returns 1 if any error was found and 0 otherwise
 */
static int8_t make_Solve_test_with_fixed_eps(ld const cur_eps)
{
    for (size_t i = 0; i < SOLVE_TEST_CNT; ++i)
    {
        Equation_roots answer = solve(&test_arr[i].eq);
        if (are_equal(&answer, &test_arr[i].roots))
        {
            continue;
        }

        printf("Test with number %d: %LG * x2 + %LG * x + %LG with eps = %LG failed\n%-30s", i,
                test_arr[i].eq.a, test_arr[i].eq.b, test_arr[i].eq.c,
                cur_eps, "Calculated roots are:");
        print_roots(&answer);
        printf("%-30s", "Must be:");
        print_roots(&test_arr[i].roots);
        return 1;
    }

    return 0;
}

/*!
 *Checks solve function for errors

 *\return Returns 1 if any error was found and 0 otherwise
 */
int8_t make_Solve_test()
{
    for (size_t i = 0; i < CNT_EPS; ++i)
    {
        set_eps(eps_test[i]);
        if (make_Solve_test_with_fixed_eps(eps_test[i]))
        {
            return 1;
        }
    }

    set_eps(default_eps);
    return 0;
}
