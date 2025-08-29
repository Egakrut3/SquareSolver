/*! \file */

#include "Roots_printer.h"
#include <math.h>

/*!
 *Prints roots from Equation_roots to output stream

 *\param[in] roots A pointer to set of roots to be printed
 */
void print_roots(Equation_roots const *const roots)
{
    assert(roots);

    switch (roots->cnt_roots)
    {
        case ANY_NUMBER_IS_ROOT:
            assert(isnan(roots->root1) and isnan(roots->root2));

            printf("Any number, since this is a trivial equation\n");
            break;

        case DEGENERATE_NO_ROOTS:
            assert(isnan(roots->root1) and isnan(roots->root2));

            printf("No real roots, since coefficients before x2 and x are equal 0 and last one - not\n");
            break;

        case SQUARE_NO_ROOTS:
            assert(isnan(roots->root1) and isnan(roots->root2));

            printf("No real roots, since discriminant is less, than 0\n");
            break;

        case LINEAR_ONE_ROOT:
            assert(isfinite(roots->root1) and isnan(roots->root2));

            printf("One root %LG, since this is a normal linear equation\n", roots->root1);
            break;

        case SQUARE_ONE_ROOT:
            assert(isfinite(roots->root1) and isnan(roots->root2));

            printf("One root %LG since discriminant is equal 0\n", roots->root1);
            break;

        case SQUARE_TWO_ROOTS:
            assert(isfinite(roots->root1) and isfinite(roots->root2));

            printf("Two roots: %LG and %LG since discriminant is greater, than 0\n", roots->root1, roots->root2);
            break;

        default:
            assert(0);

            break;
    }

    return;
}
