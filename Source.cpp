//Solves square equation of form ax2 + bx + c = 0
//is_nil - checks whether real number equal 0 or not (taking into account the inaccuracy)
//

#include <stdio.h>
#include <math.h>
#include <assert.h>

typedef long double ld;

ld const eps = 1E-9;
int const ANY_NUMBER_IS_ROOT = -1;

static inline int is_nil(ld const x)
{
    return fabsl(x) <= eps;
}

static int degenerate_solver(ld const a)
{
#ifdef _DEBUG
    assert(isfinite(a));
#endif // _DEBUG

    if (is_nil(a))
    {
        return ANY_NUMBER_IS_ROOT;
    }

    return 0;
}

static int linear_solver(ld const a, ld const b, ld *const root1)
{
#ifdef _DEBUG
    assert(isfinite(a) and isfinite(b) and root1);
#endif // _DEBUG

    if (is_nil(a))
    {
        printf_s("Since coefficient before x equal 0, this equation is degenerate, not linear. Trying to solve it...\n");
        return degenerate_solver(b);
    }

    *root1 = -b / a;
    return 1;
}

static int square_solver(ld const a, ld const b, ld const c, ld *const root1, ld *const root2)
{
#ifdef _DEBUG
    assert(isfinite(a) and isfinite(b) and isfinite(c) and root1 and root2);
#endif // _DEBUG

    if (is_nil(a))
    {
        printf_s("Since coefficient before x2 equal 0, this equation is linear, not square. Trying to solve it...\n");
        return linear_solver(b, c, root1);
    }

    ld const D2 = b * b - 4 * a * c;

    if (is_nil(D2))
    {
        *root1 = -b / (2 * a);
        return 1;
    }

    if (D2 < 0)
    {
        return 0;
    }

    ld const D = sqrtl(D2);
    *root1 = (-b - D) / (2 * a);
    *root2 = (-b + D) / (2 * a);
    return 2;
}

struct Square_equation
{
    ld a, b, c;
    Square_equation(ld const a, ld const b, ld const c) : a(a), b(b), c(c) {}
};

struct Equation_roots
{
    ld root1, root2;
    int cnt_roots;
    Equation_roots(ld const root1, ld const root2, int const cnt_roots) : root1(root1), root2(root2), cnt_roots(cnt_roots) {}
};

Square_equation get_input()
{
    printf_s("Enter coefficients of the square equation, separated by spaces\n");
    ld a = NAN, b = NAN, c = NAN;
    scanf_s("%LG%LG%LG", &a, &b, &c);

    return Square_equation(a, b, c);
}

Equation_roots solve(Square_equation const eq)
{
    ld root1 = NAN, root2 = NAN;
    const int cnt_roots = square_solver(eq.a, eq.b, eq.c, &root1, &root2);

    return Equation_roots(root1, root2, cnt_roots);
}

void make_output(Equation_roots const roots)
{
    assert(0);
    switch(roots.cnt_roots)
    {
        case ANY_NUMBER_IS_ROOT:
            printf_s("Any number is the root of this equation");
            break;

        case 0:
            printf_s("This equation has no real roots");
            break;

        case 1:
#ifdef _DEBUG
            assert(isfinite(roots.root1));
#endif // _DEBUG

            printf_s("This equation has the only real root %LG", roots.root1);
            break;

        case 2:
#ifdef _DEBUG
            assert(isfinite(roots.root1) and isfinite(roots.root2));
#endif // _DEBUG

            printf_s("This equation has two real roots: %LG and %LG", roots.root1, roots.root2);
            break;

        default:
            assert(0);
            break;
    }

    return;
}

int main()
{
    make_output(solve(get_input()));

    return 0;
}
