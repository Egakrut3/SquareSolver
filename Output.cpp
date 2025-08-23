#include "Output.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

void make_output(Equation_roots const roots)
{
    switch(roots.cnt_roots)
    {
        case ANY_NUMBER_IS_ROOT:
            printf("Any number is the root of this equation");
            break;

        case NO_ROOTS:
            printf("This equation has no real roots");
            break;

        case ONE_ROOT:
            assert(isfinite(roots.root1));

            printf("This equation has the one real root %LG", roots.root1);
            break;

        case TWO_ROOTS:
            assert(isfinite(roots.root1) and isfinite(roots.root2));

            printf("This equation has two real roots: %LG and %LG", roots.root1, roots.root2);
            break;

        default:
            abort();
            break;
    }

    return;
}
