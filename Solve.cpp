#include "Solve.h"
#include <math.h>
#include "Calculation_constants.h"

static Cnt_roots degenerate_solver(ld const a)
{
    assert(isfinite(a));

    if (is_nil(a))
    {
        return ANY_NUMBER_IS_ROOT;
    }

    return NO_ROOTS;
}

static Cnt_roots linear_solver(ld const a, ld const b, ld *const root1)
{
    assert(isfinite(a) and isfinite(b) and root1);

    if (is_nil(a))
    {
        printf("Since coefficient before x equal 0, this equation is degenerate, not linear. Trying to solve it...\n");
        return degenerate_solver(b);
    }

    *root1 = -b / a;
    return ONE_ROOT;
}

static Cnt_roots square_solver(ld const a, ld const b, ld const c, ld *const root1, ld *const root2)
{
    assert(isfinite(a) and isfinite(b) and isfinite(c) and root1 and root2);

    if (is_nil(a))
    {
        printf("Since coefficient before x2 equal 0, this equation is linear, not square. Trying to solve it...\n");
        return linear_solver(b, c, root1);
    }

    ld const D2 = b * b - 4 * a * c;

    if (is_nil(D2))
    {
        *root1 = -b / (2 * a);
        return ONE_ROOT;
    }

    if (D2 < 0)
    {
        return NO_ROOTS;
    }

    ld const D = sqrtl(D2);
    *root1 = (-b - D) / (2 * a);
    *root2 = (-b + D) / (2 * a);
    return TWO_ROOTS;
}

Equation_roots solve(Square_equation const eq)
{
    ld root1 = NAN, root2 = NAN;
    const Cnt_roots cnt_roots = square_solver(eq.a, eq.b, eq.c, &root1, &root2);
    return Equation_roots{root1, root2, cnt_roots};
}
