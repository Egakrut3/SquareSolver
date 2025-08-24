#include "Solve.h"
#include <math.h>
#include "Calculation_constants.h"

static Equation_roots degenerate_solver(ld const a)
{
    assert(isfinite(a));

    if (is_nil(a))
    {
        return Equation_roots{NAN, NAN, ANY_NUMBER_IS_ROOT};
    }

    return Equation_roots{NAN, NAN, NO_ROOTS};
}

static Equation_roots linear_solver(ld const a, ld const b)
{
    assert(isfinite(a) and isfinite(b));

    if (is_nil(a))
    {
        printf("Since coefficient before x equal 0, this equation is degenerate, not linear. Trying to solve it...\n");
        return degenerate_solver(b);
    }

    return Equation_roots{-b / a, NAN, ONE_ROOT};
}

static Equation_roots square_solver(ld const a, ld const b, ld const c)
{
    assert(isfinite(a) and isfinite(b) and isfinite(c));

    if (is_nil(a))
    {
        printf("Since coefficient before x2 equal 0, this equation is linear, not square. Trying to solve it...\n");
        return linear_solver(b, c);
    }

    ld const D2 = b * b - 4 * a * c;

    if (is_nil(D2))
    {
        return Equation_roots{-b / (2 * a), NAN, ONE_ROOT};
    }

    if (D2 < 0)
    {
        return Equation_roots{NAN, NAN, NO_ROOTS};
    }

    assert(D2 >= 0);

    ld const D = sqrtl(D2);
    return Equation_roots{(-b - D) / (2 * a), (-b + D) / (2 * a), TWO_ROOTS};
}

//TODO - make quiet in test-mode
Equation_roots solve(Square_equation const eq) //TODO - possible delete
{
    return square_solver(eq.a, eq.b, eq.c);
}
