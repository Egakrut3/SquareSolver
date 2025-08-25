#include "Output.h"
#include <math.h>

void make_output(Equation_roots const *const roots)
{
    switch (roots->cnt_roots)
    {
        case ANY_NUMBER_IS_ROOT:
            printf("Any number is the root of this equation\n");
            break;

        case NO_ROOTS:
            printf("This equation has no real roots\n");
            break;

        case ONE_ROOT:
            assert(isfinite(roots->root1));

            printf("This equation has the one real root %LG\n", roots->root1);
            break;

        case TWO_ROOTS:
            assert(isfinite(roots->root1) and isfinite(roots->root2));

            printf("This equation has two real roots: %LG and %LG\n", roots->root1, roots->root2);
            break;

        default:
            assert(0);

            break;
    }

    return;
}
