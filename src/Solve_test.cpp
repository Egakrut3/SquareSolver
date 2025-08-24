#include "Solve_test.h"
#include <math.h>
#include <Calculation_constants.h>
#include <Solve.h>

static const int SOLVE_TEST_CNT = 30, CNT_EPS = 5;

static Solve_test_instance const test_arr[SOLVE_TEST_CNT] = {
       Solve_test_instance{Square_equation{1, 2, 1}, Equation_roots{-1, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{1, -2, 1}, Equation_roots{1, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{1, 5, 6}, Equation_roots{-2, -3, TWO_ROOTS}},
       Solve_test_instance{Square_equation{1, -5, 6}, Equation_roots{2, 3, TWO_ROOTS}},
       Solve_test_instance{Square_equation{1, 2, 2}, Equation_roots{NAN, NAN, NO_ROOTS}},
       Solve_test_instance{Square_equation{1, 2, 1.001}, Equation_roots{NAN, NAN, NO_ROOTS}},
       Solve_test_instance{Square_equation{-1, -2, -1}, Equation_roots{-1, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{-1, 2, -1}, Equation_roots{1, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{-1, -5, -6}, Equation_roots{-2, -3, TWO_ROOTS}},
       Solve_test_instance{Square_equation{-1, 5, -6}, Equation_roots{2, 3, TWO_ROOTS}},
       Solve_test_instance{Square_equation{-1, -2, -2}, Equation_roots{NAN, NAN, NO_ROOTS}},
       Solve_test_instance{Square_equation{-1, -2, -1.001}, Equation_roots{NAN, NAN, NO_ROOTS}},

       Solve_test_instance{Square_equation{0, 2, 1}, Equation_roots{-0.5, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{0, 3, 1}, Equation_roots{-0.333333333333l, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{0, 1, -53}, Equation_roots{53, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{0, -2, -1}, Equation_roots{-0.5, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{0, -3, -1}, Equation_roots{-0.333333333333l, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{0, -1, 53}, Equation_roots{53, NAN, ONE_ROOT}},

       Solve_test_instance{Square_equation{0, 0, 1}, Equation_roots{NAN, NAN, NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, 0.001}, Equation_roots{NAN, NAN, NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, 1'000'000}, Equation_roots{NAN, NAN, NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, -1}, Equation_roots{NAN, NAN, NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, -0.001}, Equation_roots{NAN, NAN, NO_ROOTS}},
       Solve_test_instance{Square_equation{0, 0, -1'000'000}, Equation_roots{NAN, NAN, NO_ROOTS}},

       Solve_test_instance{Square_equation{0, 0, 0}, Equation_roots{NAN, NAN, ANY_NUMBER_IS_ROOT}},
       Solve_test_instance{Square_equation{-0, 0.00, 0E+195}, Equation_roots{NAN, NAN, ANY_NUMBER_IS_ROOT}},

       Solve_test_instance{Square_equation{1, -3, 0}, Equation_roots{0, 3, TWO_ROOTS}},
       Solve_test_instance{Square_equation{1, 0, -2}, Equation_roots{-1.4142135623730950488016887242097l, 1.4142135623730950488016887242097l, TWO_ROOTS}},
       Solve_test_instance{Square_equation{-0.76, 0, 0}, Equation_roots{0, NAN, ONE_ROOT}},
       Solve_test_instance{Square_equation{0, -3, 0}, Equation_roots{0, NAN, ONE_ROOT}},
};

static ld const eps_test[CNT_EPS] = {0.000'1, 0.000'001, 0.000'000'001, 0.000'000'000'001, 0.000'000'000'001};

int make_Solve_test()
{
    for (int i = 0; i < CNT_EPS; ++i)
    {
        set_eps(eps_test[i]);

        for (int j = 0; j < SOLVE_TEST_CNT; ++j) //TODO possible unroll
        {
            Equation_roots answer = solve(test_arr[j].eq);
            if (!are_equal(&answer, &test_arr[j].roots))
            {
                printf("Test %LG * x2 + %LG * x + %LG with eps = %LG failed\n%-30s",
                       test_arr[j].eq.a, test_arr[j].eq.b, test_arr[j].eq.c,
                       eps_test[i], "Calculated roots are:");

                switch (answer.cnt_roots)
                {
                    case ANY_NUMBER_IS_ROOT:
                        printf("Any number\n");
                        break;

                    case NO_ROOTS:
                        printf("No real roots\n");
                        break;

                    case ONE_ROOT:
                        assert(isfinite(answer.root1));

                        printf("%LG\n", answer.root1);
                        break;

                    case TWO_ROOTS:
                        assert(isfinite(answer.root1) and isfinite(answer.root2));

                        printf("%LG and %LG\n", answer.root1, answer.root2);
                        break;

                    default:
                        assert(0);

                        break;
                }

                printf("%-30s", "Must be:");

                switch (test_arr[j].roots.cnt_roots)
                {
                    case ANY_NUMBER_IS_ROOT:
                        printf("Any number\n");
                        break;

                    case NO_ROOTS:
                        printf("No real roots\n");
                        break;

                    case ONE_ROOT:
                        assert(isfinite(test_arr[j].roots.root1));

                        printf("%LG\n", test_arr[j].roots.root1);
                        break;

                    case TWO_ROOTS:
                        assert(isfinite(test_arr[j].roots.root1) and isfinite(test_arr[j].roots.root2));

                        printf("%LG and %LG\n", test_arr[j].roots.root1, test_arr[j].roots.root2);
                        break;

                    default:
                        assert(0);

                        break;
                }

                return 1;
            }
        }
    }

    return 0;
}
