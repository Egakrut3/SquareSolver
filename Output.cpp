#include "Output.h"

void make_output(Equation_roots const roots)
{
    switch(roots.cnt_roots)
    {
        case Cnt_roots::any_number_is_root:
            printf("Any number is the root of this equation");
            break;

        case Cnt_roots::no_roots:
            printf("This equation has no real roots");
            break;

        case Cnt_roots::one_root:
#ifdef _DEBUG
            assert(isfinite(roots.root1));
#endif // _DEBUG

            printf("This equation has the one real root %LG", roots.root1);
            break;

        case Cnt_roots::two_roots:
#ifdef _DEBUG
            assert(isfinite(roots.root1) and isfinite(roots.root2));
#endif // _DEBUG

            printf("This equation has two real roots: %LG and %LG", roots.root1, roots.root2);
            break;

        default:
            assert(0);
            break;
    }

    return;
}
