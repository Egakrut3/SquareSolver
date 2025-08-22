#include "Solve.h"

ld const eps = 1E-9;

static inline int is_nil(ld const x)
{
    return fabsl(x) <= eps;
}

static Cnt_roots degenerate_solver(ld const a)
{
#ifdef _DEBUG
    assert(isfinite(a));
#endif // _DEBUG

    if (is_nil(a))
    {
        return Cnt_roots::any_number_is_root;
    }

    return Cnt_roots::no_roots;
}

static Cnt_roots linear_solver(ld const a, ld const b, ld *const root1)
{
#ifdef _DEBUG
    assert(isfinite(a) and isfinite(b) and root1);
#endif // _DEBUG

    if (is_nil(a))
    {
        printf("Since coefficient before x equal 0, this equation is degenerate, not linear. Trying to solve it...\n");
        return degenerate_solver(b);
    }

    *root1 = -b / a;
    return Cnt_roots::one_root;
}

static Cnt_roots square_solver(ld const a, ld const b, ld const c, ld *const root1, ld *const root2)
{
#ifdef _DEBUG
    assert(isfinite(a) and isfinite(b) and isfinite(c) and root1 and root2);
#endif // _DEBUG

    if (is_nil(a))
    {
        printf("Since coefficient before x2 equal 0, this equation is linear, not square. Trying to solve it...\n");
        return linear_solver(b, c, root1);
    }

    ld const D2 = b * b - 4 * a * c;

    if (is_nil(D2))
    {
        *root1 = -b / (2 * a);
        return Cnt_roots::one_root;
    }

    if (D2 < 0)
    {
        return Cnt_roots::no_roots;
    }

    ld const D = sqrtl(D2);
    *root1 = (-b - D) / (2 * a);
    *root2 = (-b + D) / (2 * a);
    return Cnt_roots::two_roots;
}

Equation_roots solve(Square_equation const eq)
{
    ld root1 = NAN, root2 = NAN;
    const Cnt_roots cnt_roots = square_solver(eq.a, eq.b, eq.c, &root1, &root2);

    return Equation_roots{root1, root2, cnt_roots};
}
